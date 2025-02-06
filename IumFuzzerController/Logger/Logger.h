#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <iomanip>
#include "../../interface/IumFuzzer.h"

class Logger
{
private:
    std::ofstream logFile;

public:
    explicit Logger(const std::string& fileName);

    ~Logger();

    void log(const IUM_SYSTEM_CALL_DATA* callData);
};


#endif
