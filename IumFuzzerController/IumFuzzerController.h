#pragma once

#define WIN32_LEAN_AND_MEAN   

// RPC underlaying protocol
#define TRUSTLET_RPC_PROT "ncalrpc"

// ALPC endpoint name
#define TRUSTLET_RPC_NAME "IumFuzzer"

#include <SDKDDKVer.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <tchar.h>

#include <iostream>

#include "../interface/IumFuzzer.h"

#include "FuzzInputParser/FuzzInputParser.h"
#include "CaseGenerator/CaseGenerator.h"
#include "Logger/Logger.h"