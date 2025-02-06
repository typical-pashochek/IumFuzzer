#include "FuzzInputParser.h"

FuzzInputParser::FuzzInputParser(const std::string& filename)
{
    file.open(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}


FuzzInputParser::~FuzzInputParser()
{
    if (file.is_open())
    {
        file.close();
    }
}


void FuzzInputParser::getNextArgs(IUM_SYSTEM_CALL_DATA* callData)
{
    if (std::getline(file, currentLine))
    {
        int scn, argsCount;
        std::istringstream lineStream(currentLine);
        std::vector<uint64_t> inputParameters;

        if (!(lineStream >> scn))
        {
            throw std::runtime_error("Invalid format: missing or invalid scn");
        }

        if (!(lineStream >> argsCount))
        {
            throw std::runtime_error("Invalid format: missing or invalid argsCount");
        }

        for (int i = 0; i < argsCount; i++)
        {
            std::string hexData;
            int size;

            if (!(lineStream >> size >> hexData))
            {
                throw std::runtime_error("Invalid format: missing or invalid size or arg");
            }

            if (size == 0)
            {
                *(PUINT64)callData->args[i].value = std::stoull(hexData, nullptr, 16);
            }
            else
            {
                parseHexToMemory(callData->args[i].value, hexData);
            }

            callData->args[i].size = size;
        }

        callData->scn = scn;
        callData->argsCount = argsCount;
    }
}


bool FuzzInputParser::hasMoreArgs() const
{
    return !file.eof();
}


void FuzzInputParser::parseHexToMemory(unsigned char* memory, std::string& hexData)
{
    size_t dataSize = hexData.size() / 2;

    for (size_t i = 0; i < dataSize; ++i)
    {
        std::string byteString = hexData.substr(i * 2, 2);
        memory[i] = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
    }

    return;
}