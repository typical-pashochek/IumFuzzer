

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 08:14:07 2038
 */
/* Compiler settings for IumFuzzer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __IumFuzzer_h__
#define __IumFuzzer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IumFuzzer_INTERFACE_DEFINED__
#define __IumFuzzer_INTERFACE_DEFINED__

/* interface IumFuzzer */
/* [version][uuid] */ 

typedef unsigned __int64 UINT64;

typedef /* [public][public] */ struct __MIDL_IumFuzzer_0001
    {
    unsigned long bufferLength;
    /* [size_is][unique] */ byte *buffer;
    } 	IDENTITY_KEY;

typedef /* [public][public][public] */ struct __MIDL_IumFuzzer_0002
    {
    UINT64 size;
    unsigned char value[ 4096 ];
    } 	IUM_SYSTEM_CALL_ARG;

typedef /* [public][public] */ struct __MIDL_IumFuzzer_0003
    {
    UINT64 scn;
    UINT64 argsCount;
    IUM_SYSTEM_CALL_ARG args[ 12 ];
    } 	IUM_SYSTEM_CALL_DATA;

void SendData( 
    /* [in] */ handle_t IDL_handle,
    /* [string][in] */ const unsigned char *data);

void ReceiveData( 
    /* [in] */ handle_t IDL_handle,
    /* [string][out] */ unsigned char **pData);

void Terminate( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ unsigned long code);

error_status_t GetIdentityKey( 
    /* [in] */ handle_t IDL_handle,
    /* [out] */ IDENTITY_KEY *pKey);

UINT64 IumSystemCall( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ IUM_SYSTEM_CALL_DATA *pData);



extern RPC_IF_HANDLE IumFuzzer_v1_0_c_ifspec;
extern RPC_IF_HANDLE IumFuzzer_v1_0_s_ifspec;
#endif /* __IumFuzzer_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


