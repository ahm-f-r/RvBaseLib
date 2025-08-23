#ifndef RV_BASE_ENUM_H
#define RV_BASE_ENUM_H

#include "RvBaseCommon.d"

// ============================================================================
namespace RvAddrEnums 
// ============================================================================
{
  enum AddrType {
    cPhysical   = 0,
    cLogical    = 1,
    cEffective  = 2
  };
  enum StorageType {
    cRegister   = 0,
    cMemory     = 1, 
    cDevice     = 2
  };
  enum OffsetType {
    cCacheLine  = 0,
    cPage       = 1
  };
  enum WordSize {
    cByte       = 0, 
    cHWord      = 1,
    cWord       = 2,
    cDWord      = 3,
    cQWord      = 4
  };
  enum CacheLineSize {
    cSize32B    = 5,
    cSize64B    = 6,
    cSize128B   = 7,
    cSize256B   = 8,
    cSize512B   = 9
  };
  enum PageSize {
    cSize1k     = 10,
    cSize2k     = 11,
    cSize4k     = 12,
    cSize8k     = 13,
    cSize16k    = 14,
    cSize1M     = 20,
    cSize2M     = 21,
    cSize4M     = 22,
    cSize8M     = 23,
    cSize16M    = 24,
    cSize1G     = 30
  };
}

// ============================================================================
namespace RvDataEnums
// ============================================================================
{
  enum DataMask {
    cDwordHi    = 0xffffffff00000000,
    cDwordLo    = 0x00000000ffffffff,
    cWordHi     = 0x00000000ffff0000, 
    cWordLo     = 0x000000000000ffff,
    cHwordHi    = 0x000000000000ff00,
    cHwordLo    = 0x00000000000000ff,
    cByteHi     = 0x00000000000000f0,
    cByteLo     = 0x000000000000000f
  };
}

// ============================================================================
namespace RvCsvEnums
// ============================================================================
{
  enum CsvColumn {
    cScope  = 0,
    cName   = 1,
    cType   = 2,
    cValue  = 3
  };
} 

#endif
