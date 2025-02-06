#pragma once

#define WIN32_LEAN_AND_MEAN             

#include <SDKDDKVer.h>

#include <stdint.h>
#include <windows.h>
#include <stdio.h>

#include "include/iumbase.h"

#include "../interface/IumFuzzer.h"

// RPC underlaying protocol
#define TRUSTLET_RPC_PROT "ncalrpc"

// ALPC endpoint name
#define TRUSTLET_RPC_NAME "IumFuzzer"

using IumSystemCallFunction = UINT64(*) (...);