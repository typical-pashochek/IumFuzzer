#ifndef FUZZ_INPUT_PARSER_H
#define FUZZ_INPUT_PARSER_H
#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <Windows.h>
#include "../../interface/IumFuzzer.h"

class FuzzInputParser
{
private:
    std::ifstream file;
    std::string currentLine;


public:
    explicit FuzzInputParser(const std::string& filename);

    ~FuzzInputParser();

    void getNextArgs(IUM_SYSTEM_CALL_DATA* callData);

    bool hasMoreArgs() const;

private:

    void parseHexToMemory(unsigned char* memory, std::string& hexData);
};

#endif
