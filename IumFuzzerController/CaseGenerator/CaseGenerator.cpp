#include "CaseGenerator.h"
#include <random>
#include <sstream>

void CaseGenerator::generate(int syscallNumber, IUM_SYSTEM_CALL_DATA* callData)
{
    uint64_t arg;
    callData->scn = syscallNumber;

    switch (syscallNumber)
    {
    //IumAssignMemoryToSocDomain
    case 0x8000000:
        callData->argsCount = 0;
        break;
    //IumAwaitSmc
    case 0x8000001:
        callData->argsCount = 0;
        break;
    //IumCreateSecureDevice
    case 0x8000002:
        callData->argsCount = 2;

        callData->args[0].size = 0;
        arg = generateRandomInt() % 10;
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));
    //IumCreateSecureSection
    case 0x8000003:
        callData->argsCount = 6;

        callData->args[0].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = sizeof(uint64_t);
        callData->args[1].value[0] = 36;

        callData->args[2].size = 0;
        callData->args[2].value[0] = 4;

        callData->args[3].size = 0;
        callData->args[3].value[0] = 4;

        callData->args[4].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[4].value, &arg, sizeof(uint64_t));

        callData->args[5].size = 0;
        callData->args[5].value[0] = 0;
        break;
    case 0x8000004:
        callData->argsCount = 0;
        break;
    case 0x8000005:
        callData->argsCount = 0;
        break;
    case 0x8000006:
        callData->argsCount = 0;
        break;
    case 0x8000007:
        callData->argsCount = 0;
        break;
    case 0x8000008:
        callData->argsCount = 0;
        break;
    case 0x8000009:
        callData->argsCount = 0;
        break;
    case 0x800000A:
        callData->argsCount = 0;
        break;
    //IumGetIdk
    case 0x800000B:
        callData->argsCount = 3;

        callData->args[0].size = 0;
        callData->args[0].value[0] = generateRandomInt() % 2;

        callData->args[1].size = sizeof(uint64_t);
        callData->args[1].value[0] = 1;

        callData->args[2].size = sizeof(uint64_t);
        arg = generateRandomInt() % 0x31200;
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));

        break;
    case 0x800000C:
        callData->argsCount = 0;
        break;
    case 0x800000D:
        callData->argsCount = 0;
        break;
    //IumOpenSecureSection
    case 0x800000E:
        callData->argsCount = 2;

        callData->args[0].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = sizeof(uint64_t);
        arg = 36;
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));
        break;
    //IumPostMailbox
    case 0x800000F:
        callData->argsCount = 0;
        break;
    //IumProtectSecureIo
    case 0x8000010:
        callData->argsCount = 3;

        callData->args[0].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[0].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));

        callData->args[0].size = 0;
        arg = generateRandomInt() % 5;
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));
        break;
    //IumQuerySecureDeviceInformation
    case 0x8000011:
        callData->argsCount = 4;

        callData->args[0].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = 0;
        arg = generateRandomInt() % 5;
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));

        callData->args[2].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));

        callData->args[3].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[3].value, &arg, sizeof(uint64_t));
        break;
    // IumSecureStorageGet
    case 0x8000012:
        callData->argsCount = 3;

        callData->args[0].size = 0;
        callData->args[0].value[0] = generateRandomInt() % 2;

        callData->args[1].size = sizeof(uint64_t);
        callData->args[1].value[0] = 1;

        callData->args[2].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));
        break;
    //IumSecureStoragePut
    case 0x8000013:
        callData->argsCount = 3;

        callData->args[0].size = 0;
        arg = generateRandomInt() % 2;
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = sizeof(uint64_t);
        arg = generateRandomInt();
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));

        callData->args[2].size = 0;
        arg = generateRandomInt() % 0xFF9;
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));
        break;
    //IumSetDmaTargetProperties
    case 0x8000014:
        callData->argsCount = 3;

        callData->args[0].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[1].value, &arg, sizeof(uint64_t));

        callData->args[2].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[2].value, &arg, sizeof(uint64_t));

        break;
    //IumSetPolicyExtension
    case 0x8000015:
        callData->argsCount = 1;

        callData->args[0].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));
        break;
    //IumUnmapSecureIo
    case 0x8000016:
        callData->argsCount = 1;

        callData->args[0].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));
        break;
    //IumUpdateSecureDeviceState
    case 0x8000017:
        callData->argsCount = 2;

        callData->args[0].size = 0;
        arg = generateRandomInt();
        std::memcpy(callData->args[0].value, &arg, sizeof(uint64_t));

        callData->args[1].size = 0;
        arg = generateRandomInt() % 3;
        std::memcpy(callData->args[1].value, &arg, sizeof(char));
        break;
    default:
        break;
    }
}

void CaseGenerator::mutate(IUM_SYSTEM_CALL_DATA* originalCallData, IUM_SYSTEM_CALL_DATA* mutatedCallData)
{
    std::memcpy(mutatedCallData, originalCallData, sizeof(IUM_SYSTEM_CALL_DATA));

    for (size_t argIndex = 0; argIndex < originalCallData->argsCount; argIndex++)
    {
        int mutationType = generateRandomInt() % 5;
        uint64_t size = mutatedCallData->args[argIndex].size;
        if (size == 0)
            size = sizeof(UINT64);

        switch (mutationType)
        {
        case 0:
            // no mutation
            break;
        case 1:
            bitflip(mutatedCallData->args[argIndex].value, size);
            break;
        case 2:
            replaceByteRandom(mutatedCallData->args[argIndex].value, size);
            break;
        case 3:
            replaceBlockRandom(mutatedCallData->args[argIndex].value, size);
            break;
        case 4:
            replaceValueSpecial(mutatedCallData->args[argIndex].value, size);
            break;
        default:
            break;
        }
    }
}


uint64_t CaseGenerator::generateRandomInt()
{
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);
    return dis(gen);
}

void CaseGenerator::bitflip(BYTE* value, uint64_t size)
{
    uint64_t index = generateRandomInt() % size;
    uint64_t bitPos = generateRandomInt() % 8;
    value[index] ^= (1 << bitPos);
}

void CaseGenerator::replaceByteRandom(BYTE* value, uint64_t size)
{
    uint64_t index = generateRandomInt() % size;
    value[index] = static_cast<BYTE>(generateRandomInt() & 0xFF);
}

void CaseGenerator::replaceBlockRandom(BYTE* value, uint64_t size)
{
    uint64_t startIndex = generateRandomInt() % size;
    uint64_t endIndex = generateRandomInt() % size;

    if (startIndex > endIndex)
        std::swap(startIndex, endIndex);

    for (uint64_t i = startIndex; i < endIndex; i++)
    {
        value[i] = static_cast<BYTE>(generateRandomInt() & 0xFF);
    }
}

void CaseGenerator::replaceValueSpecial(BYTE* value, uint64_t size)
{
    if (size < sizeof(uint64_t))
        return;

    uint64_t arg = specialValues[generateRandomInt() % specialValues.size()];
    std::memcpy(value, &arg, sizeof(uint64_t));
}
