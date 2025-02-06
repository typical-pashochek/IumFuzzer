#include "IumFuzzer.h"

//extern "C" int __fastcall sys_call(UINT64 arg);

// image policy section
#pragma section(IMAGE_POLICY_SECTION_NAME, read)

// trustlet instance GUID
__declspec(allocate(IMAGE_POLICY_SECTION_NAME))
const char m_ScenarioId[] = "{8059e825-a3e7-47a1-bf46-ac02991067fb}";

// trustlet application ID
#define APPLICATION_ID 1
#define ALLOW_DEBUG 1

IMAGE_POLICY_START(APPLICATION_ID)
IMAGE_POLICY_UINT32(ImagePolicyIdEtw, 0)
IMAGE_POLICY_UINT32(ImagePolicyIdDebug, ALLOW_DEBUG)
IMAGE_POLICY_UINT32(ImagePolicyIdCrashDump, 0)
IMAGE_POLICY_UINT64(ImagePolicyIdCapability, 3)
IMAGE_POLICY_ANSI_STRING(ImagePolicyIdScenarioId, m_ScenarioId)
IMAGE_POLICY_END()

uint8_t* m_identity_key = NULL;
char sym = 0;
unsigned long m_identity_key_size = 0;
const unsigned char* m_user_data;


char* iumSysCallNames[24] = {
    "IumAssignMemoryToSocDomain",
    "IumAwaitSmc",
    "IumCreateSecureDevice",
    "IumCreateSecureSection",
    "IumCreateSecureSectionSpecifyPages",
    "IumCrypto",
    "IumDmaMapMemory",
    "IumEmitSmc",
    "IumFlushSecureSectionBuffers",
    "IumGetDmaEnabler",
    "IumGetExposedSecureSection",
    "IumGetIdk",
    "IumMapSecureIo",
    "IumOpenCurrentExtension",
    "IumOpenSecureSection",
    "IumPostMailbox",
    "IumProtectSecureIo",
    "IumQuerySecureDeviceInformation",
    "IumSecureStorageGet",
    "IumSecureStoragePut",
    "IumSetDmaTargetProperties",
    "IumSetPolicyExtension",
    "IumUnmapSecureIo",
    "IumUpdateSecureDeviceState"
};

//--------------------------------------------------------------------------------------
/*
    Memory allocation function for RPC
*/
void* __RPC_USER midl_user_allocate(size_t size)
{
    return LocalAlloc(LMEM_FIXED, size);
}

/*
    Memory deallocation function for RPC
*/
void __RPC_USER midl_user_free(void* ptr)
{
    LocalFree(ptr);
}

/*
    Terminate trustlet RPC call handler
*/
void Terminate(handle_t IDL_handle, unsigned long code)
{
    ExitProcess(code);
}


void* MemCopy(void* dest, const void* src, size_t n) 
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) 
    {
        d[i] = s[i];
    }

    return dest;
}


/*
    Get identity key RPC call handler
*/
error_status_t GetIdentityKey(handle_t IDL_handle, IDENTITY_KEY* pKey)
{
    if (m_identity_key && m_identity_key_size > 0)
    {
        // allocate memory for return data
        if ((pKey->buffer = (byte*)MIDL_user_allocate(m_identity_key_size)) == NULL)
        {
            return RPC_S_OUT_OF_MEMORY;
        }

        pKey->bufferLength = m_identity_key_size;
        MemCopy(pKey->buffer, m_identity_key, m_identity_key_size);

        return RPC_S_OK;
    }

    return RPC_S_INTERNAL_ERROR;
}

void SendData(handle_t IDL_handle, const unsigned char* data) 
{
    sym = data[0];
}

void ReceiveData(handle_t IDL_handle, unsigned char** data) 
{
    *data = (unsigned char*)MIDL_user_allocate(sizeof("Hello"));
    
    if (sym == 5)
        MemCopy(*data, "Hello", sizeof("Hello"));
    else
        MemCopy(*data, "olleH", sizeof("Hello"));
}


UINT64 IumSystemCall(handle_t IDL_handle, IUM_SYSTEM_CALL_DATA* pData)
{
    HMODULE iumdll = GetModuleHandle(TEXT("iumdll.dll"));
    if (!iumdll)
        return RPC_S_INTERNAL_ERROR;

    if (pData->scn < 0x8000000)
        return RPC_S_INTERNAL_ERROR;

    IumSystemCallFunction iumSystemCallFunction = reinterpret_cast<IumSystemCallFunction>(GetProcAddress(iumdll, iumSysCallNames[pData->scn - 0x8000000]));
    if (!iumSystemCallFunction)
        return RPC_S_INTERNAL_ERROR;

    UINT64 args[12];

    for (int i = 0; i < pData->argsCount; i++)
    {
        if (pData->args[i].size == 0)
        {
            args[i] = *(PUINT64)(pData->args[i].value);
        }
        else
        {
            args[i] = (UINT64)pData->args[i].value;
        }
    }

    return iumSystemCallFunction(
                args[0],
                args[1], 
                args[2], 
                args[3], 
                args[4], 
                args[5], 
                args[6], 
                args[7], 
                args[8],
                args[9],
                args[10],
                args[11]
            );
}

//--------------------------------------------------------------------------------------
int RpcStart(void)
{
    // initialize local RPC
    RPC_STATUS status = RpcServerUseProtseqEpA(
        (RPC_CSTR)TRUSTLET_RPC_PROT, RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
        (RPC_CSTR)TRUSTLET_RPC_NAME, NULL
    );
    if (status != RPC_S_OK)
    {
        return -1;
    }

    // register the IumFuzzer interface
    status = RpcServerRegisterIf(IumFuzzer_v1_0_s_ifspec, NULL, NULL);
    if (status != RPC_S_OK)
    {
        return -1;
    }

    // start to listen for remote procedure calls for all registered interfaces
    status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, 0);
    if (status != RPC_S_OK)
    {
        return -1;
    }

    return 0;
}

int RpcStop(void)
{
    // stop RPC server
    RPC_STATUS status = RpcMgmtStopServerListening(NULL);
    if (status != RPC_S_OK)
    {
        return -1;
    }

    return 0;
}

int main() 
{

    // check if current process is running in VTL1
    if (!IsSecureProcess())
    {
        return -1;
    }

    // determine secure identy key size
    if (!GetSecureIdentityKey(m_identity_key, &m_identity_key_size) && m_identity_key_size > 0)
    {
        if ((m_identity_key = (uint8_t*)LocalAlloc(LMEM_FIXED, m_identity_key_size)) != NULL)
        {
            // get secure identy key data
            if (!GetSecureIdentityKey(m_identity_key, &m_identity_key_size))
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    // start RPC server
    if (RpcStart() != 0)
    {
        return -1;
    }

    return 0;
}
