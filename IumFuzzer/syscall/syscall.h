#include <stdint.h>
#include <windows.h>

using ScIumAssignMemoryToSocDomain = 
UINT64(*) (
	UINT64	arg //unknown
);

using ScIumAwaitSmc =
UINT64(*) (
	 UINT64	arg //unknown
);

using ScIumCreateSecureDevice =
UINT64(*) (
	 UINT64	arg1,
	 UINT64	arg2
);

using ScIumCreateSecureSection =
UINT64(*) (
	 UINT64* arg1,
	 int arg2,
	 INT64 arg3,
	 int arg4,
	 unsigned int arg5,
	 int arg6
);

using ScIumCreateSecureSectionSpecifyPages =
UINT64(*) (
	 UINT64	arg
);

using ScIumCrypto =
UINT64(*) (
	 unsigned char* arg
);

using ScIumDmaMapMemory =
UINT64(*) (
	 INT64 arg1,
	 INT64 arg2,
	 int arg3,
	 UINT64 arg4,
	 int arg5,
	 UINT64* arg6,
	 UINT64* Address,
	 UINT64* arg8);

using ScIumEmitSmc =
UINT64(*) (
);

using ScIumFlushSecureSectionBuffers =
UINT64(*) (
	 int	arg1,
	 UINT64	arg2,
	 INT64	arg3
);

using ScIumGetDmaEnabler =
UINT64(*) (
	 INT64	arg1,
	 UINT64	arg2,
	 UINT64* arg3
);

using ScIumGetExposedSecureSection =
UINT64(*) (
	 UINT64* arg1,
	 int arg2
);

using ScIumGetIdk =
UINT64(*) (
	 int 	arg1,
	 UINT64 pVoid,
	 UINT64* arg3
);

using ScIumMapSecureIo =
UINT64(*) (
	 int arg1,
	 INT64 arg2,
	 INT64 arg3,
	 int arg4,
	 INT64 arg5,
	 UINT64* arg6
);

using ScIumOpenCurrentExtension =
UINT64(*) (
	 UINT64	arg //unknown
);

using ScIumOpenSecureSection =
UINT64(*) (
	 UINT64* arg1,
	 INT64	arg2
);

using ScIumPostMailbox =
UINT64(*) (
	 unsigned int	arg1,
	 unsigned char* arg2,
	 UINT64	arg3
);

using ScIumProtectSecureIo =
UINT64(*) (
	 UINT64* arg1,
	 INT64* arg2,
	 int	arg3
);

using ScIumQuerySecureDeviceInformation =
UINT64(*) (
	 INT64	arg1,
	 INT64	arg2,
	 INT64	arg3,
	 INT64	arg4
);

using ScIumSecureStorageGet =
UINT64(*) (
	 unsigned int	arg1,
	 UINT64 pVoid,
	 UINT64* arg3
);

using ScIumSecureStoragePut =
UINT64(*) (
	 unsigned int arg1,
	 UINT64 arg2,
	 INT64	arg3
);

using ScIumSetDmaTargetProperties =
UINT64(*) (
	 INT64			arg1,
	 INT64			arg2,
	 unsigned int	arg3
);

using ScIumSetPolicyExtension =
UINT64(*) (
	 INT64	arg
);

using ScIumUnmapSecureIo =
UINT64(*) (
	 UINT64	arg
);

using ScIumUpdateSecureDeviceState =
UINT64(*) (
	 INT64	arg1,
	 INT64	arg2
);