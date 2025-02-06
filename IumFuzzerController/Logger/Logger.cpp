#include "Logger.h"

Logger::Logger(const std::string& fileName)
{
    logFile.open(fileName, std::ios::out | std::ios::app);
    if (!logFile.is_open())
    {
        throw std::runtime_error("Unable to open log file: " + fileName);
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void Logger::log(const IUM_SYSTEM_CALL_DATA* callData)
{
    if (logFile.is_open())
    {
        logFile << callData->scn << " ";

        logFile << callData->argsCount << " ";

        for (size_t i = 0; i < callData->argsCount; i++)
        {
            logFile << callData->args[i].size << " ";

            size_t length = callData->args[i].size ? callData->args[i].size : sizeof(UINT64);
            
            for (size_t j = 0; j < length; j++)
            {
                logFile << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(callData->args[i].value[j]) << std::dec;
            }

            logFile << " ";

        }

        logFile << std::endl;
        logFile.flush();
    }
    else
    {
        throw std::runtime_error("Log file is not open");
    }
}
