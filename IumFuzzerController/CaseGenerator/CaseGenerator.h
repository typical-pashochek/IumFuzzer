#ifndef CASE_GENERATOR_H
#define CASE_GENERATOR_H

#include <string>
#include <vector>

#include "../../interface/IumFuzzer.h"


class CaseGenerator
{
public:
    void generate(int syscallNumber, IUM_SYSTEM_CALL_DATA* callData);
    void mutate(IUM_SYSTEM_CALL_DATA* originalCallData, IUM_SYSTEM_CALL_DATA* mutatedCallData);

private:
    static uint64_t generateRandomInt();

    void bitflip(BYTE* value, uint64_t size);
    void replaceByteRandom(BYTE* value, uint64_t size);
    void replaceBlockRandom(BYTE* value, uint64_t size);
    void replaceValueSpecial(BYTE* value, uint64_t size);

    std::vector<int64_t> specialValues = {
        0,
        1,
        -1,
        SHRT_MAX,
        SHRT_MIN,
        USHRT_MAX,
        INT_MAX,
        INT_MIN,
        UINT_MAX,
        LONG_MIN,
        LONG_MAX,
        ULONG_MAX,
        0xCCCCCCCC,
        0x90909090
    };
};

#endif // CASE_GENERATOR_H
