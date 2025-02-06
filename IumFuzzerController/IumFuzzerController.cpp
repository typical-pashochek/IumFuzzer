#include "IumFuzzerController.h"

extern bool m_quiet;

HANDLE m_rpc_thread = NULL;
//--------------------------------------------------------------------------------------

handle_t RpcInitialize(void)
{
    handle_t binding = NULL;
    RPC_CSTR binding_string = NULL;

    // generate binding string
    RPC_STATUS status = RpcStringBindingComposeA(
        NULL,
        (RPC_CSTR)TRUSTLET_RPC_PROT, NULL,
        (RPC_CSTR)TRUSTLET_RPC_NAME, NULL,
        &binding_string
    );

    if (status != RPC_S_OK)
    {
        return NULL;
    }

    // create server binding handle
    status = RpcBindingFromStringBindingA(binding_string, &binding);

    if (status != RPC_S_OK)
    {
        return NULL;
    }

    return binding;
}

int RpcUninitialize(handle_t binding)
{
    RPC_STATUS status = RpcBindingFree(&binding);

    return status == RPC_S_OK ? 0 : -1;
}

int RpcTerminate(handle_t binding, unsigned long code)
{
    RpcTryExcept
    {
        Terminate(binding, code);
    }
        RpcExcept(1)
    {
        return -1;
    }
    RpcEndExcept

        return 0;
}

int RpcGetIdentityKey(handle_t binding, uint8_t** key_data, size_t* key_size)
{
    IDENTITY_KEY key;

    key.buffer = NULL;
    key.bufferLength = 0;

    RpcTryExcept
    {
        RPC_STATUS status = GetIdentityKey(binding, &key);
        if (status != RPC_S_OK)
        {
            return -1;
        }

        *key_data = key.buffer;
        *key_size = key.bufferLength;
    }
        RpcExcept(1)
    {
        return -1;
    }
    RpcEndExcept

        return 0;
}


int RpcReceiveData(handle_t binding, unsigned char** data)
{

    RpcTryExcept
    {
        ReceiveData(binding, data);
    }
        RpcExcept(1)
    {
        return -1;
    }
    RpcEndExcept

        return 0;
}


int RpcSendData(handle_t binding, unsigned char* data)
{

    RpcTryExcept
    {
        SendData(binding, data);
    }
        RpcExcept(1)
    {
        return -1;
    }
    RpcEndExcept

        return 0;
}


UINT64 RpcIumSystemCall(handle_t binding, IUM_SYSTEM_CALL_DATA *pData)
{
    UINT64 result;
    RpcTryExcept
    {
        result = IumSystemCall(binding, pData);
        
        // printf("[+] IUM system call %llx: %llx\n", pData->scn, result);
    }
        RpcExcept(1)
    {
        return -1;
    }
    RpcEndExcept

        return result;
}


//--------------------------------------------------------------------------------------

// Memory allocation and deallocation required by RPC
void* __RPC_USER midl_user_allocate(size_t len) 
{
    return LocalAlloc(LMEM_FIXED, len);
    //return malloc(len);
}

void __RPC_USER midl_user_free(void* ptr) 
{
    free(ptr);
}


void Hexdump(const void* buffer, size_t size)
{
    const unsigned char* data = (const unsigned char*)buffer;
    size_t offset = 0;

    while (offset < size) 
    {
        printf("%08lx  ", offset);

        for (size_t i = 0; i < 16; i++) 
        {
            if (offset + i < size) 
            {
                printf("%02x ", data[offset + i]);
            }
            else 
            {
                printf("   ");
            }
        }

        printf(" ");

        for (size_t i = 0; i < 16; i++) 
        {
            if (offset + i < size) 
            {
                unsigned char ch = data[offset + i];
                printf("%c", isprint(ch) ? ch : '.');
            }
        }

        printf("\n");
        offset += 16;
    }
}


void GenerateBasis(handle_t binding)
{
    printf("[+] Generating basis\n");

    IUM_SYSTEM_CALL_DATA* callData = (IUM_SYSTEM_CALL_DATA*)malloc(sizeof(IUM_SYSTEM_CALL_DATA));

    if (callData == 0)
    {
        printf(__FUNCTION__"() ERROR: unable to allocate callData\n");
        return;
    }

    CaseGenerator caseGenerator;
    Logger logger("case.txt");
    UINT64 retValue;
    UINT64 caseCount = 0;

    for (UINT64 callCode = 0x8000000; callCode <= 0x8000017; callCode++)
    {
        for (int i = 0; i < 1000; i++)
        {
            caseGenerator.generate(callCode, callData);
            retValue = RpcIumSystemCall(binding, callData);

            if (retValue != 0xC000000D)
            {
                logger.log(callData);
                caseCount++;
            }
        }
    }

    free(callData);

    printf("[+] Generation done: %llu cases\n", caseCount);
}


void Fuzz(handle_t binding, uint64_t mutationsCount)
{
    printf("[+] Start fuzzing\n");

    IUM_SYSTEM_CALL_DATA* originalCallData = (IUM_SYSTEM_CALL_DATA*)malloc(sizeof(IUM_SYSTEM_CALL_DATA));
    IUM_SYSTEM_CALL_DATA* mutatedCallData = (IUM_SYSTEM_CALL_DATA*)malloc(sizeof(IUM_SYSTEM_CALL_DATA));

    if (originalCallData == 0 || mutatedCallData == 0)
    {
        printf(__FUNCTION__"() ERROR: unable to allocate callData\n");
        return;
    }    

    CaseGenerator caseGenerator;
    FuzzInputParser fuzzInputParser("case.txt");
    Logger logger("output.txt");
    size_t counter = 0;

    while (fuzzInputParser.hasMoreArgs())
    {
        fuzzInputParser.getNextArgs(originalCallData);

        for (int caseCount = 0; caseCount < mutationsCount; caseCount++)
        {
            caseGenerator.mutate(originalCallData, mutatedCallData);

            logger.log(mutatedCallData);

            UINT64 retValue = RpcIumSystemCall(binding, mutatedCallData);
            
            std::cout << "\rCase " << counter << ": " << "callCode = " << std::hex << mutatedCallData->scn << " retValue = " << retValue << std::flush;
            counter++;
        }
    }

    free(originalCallData);
    free(mutatedCallData);
}


void main()
{
    printf("[+] Creating RPC binding...\n");

    handle_t binding = RpcInitialize();


    if (!binding)
    {
        printf(__FUNCTION__"() ERROR: unable to create RPC server binding\n");
    }


    uint8_t* key_data = NULL;
    size_t key_size = 0;
    uint8_t* data = 0;

    /*printf("[+] Calling RPC server to obtain trustlet identy key...\n");

    // perform RPC call to get trustlet identy key
    if (RpcGetIdentityKey(binding, &key_data, &key_size) == 0)
    {
        printf("[+] Trustlet identy key size is %d bytes\n", key_size);

        Hexdump(key_data, (uint32_t)key_size);
        free(key_data);
    }
    else
    {
        printf(__FUNCTION__"() ERROR: unable to get trustlet identy key\n");
    }*/

    printf("[+] Calling RPC server to receive data...\n");

    if (RpcReceiveData(binding, &data) == 0)
    {
        printf("[+] Data received\n");
        Hexdump(data, (uint32_t)strlen((const char*)data));
    }
    else
    {
        printf(__FUNCTION__"() ERROR: unable to receive data\n");
    }    

    try
    {
        GenerateBasis(binding);
        Fuzz(binding, 100);
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
    }    

    //printf("[+] Calling RPC server to terminate running trustlet...\n");

    // perform RPC call to terminate trustlet process
    /*if (RpcTerminate(binding, 0))
    {
        printf("[+] Secure process exit\n");
    }
    else
    {
        printf(__FUNCTION__"() ERROR: unable to terminate runing trustlet\n");
    }*/

    RpcUninitialize(binding);
}