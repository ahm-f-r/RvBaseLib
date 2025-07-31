#ifndef RV_BASE_ENUM_H
#define RV_BASE_ENUM_H

namespace RvAddrEnums {
  enum eAddrType {
    SysRegAddr      = 0,
    DeviceAddr      = 1,
    MemoryAddr      = 2,
    PhysicalAddr    = 3,
    VirtualAddr     = 4,
    CacheLineAddr   = 5,
    PageAddr        = 6
  };
  enum eOffsetType {
    CacheLineOffset = 0,
    PageOffset      = 1
  };
  enum eWordSize {
    Byte  = 0, 
    HWord = 1,
    Word  = 2,
    DWord = 3,
    QWord = 4
  };
  enum eCacheLineSize {
    Size32B   = 5,
    Size64B   = 6,
    Size128B  = 7,
    Size256B  = 8,
    Size512B  = 9
  };
  enum ePageSize {
    Size1k  = 10,
    Size2k  = 11,
    Size4k  = 12,
    Size8k  = 13,
    Size16k = 14,
    Size1M  = 20,
    Size2M  = 21,
    Size4M  = 22,
    Size8M  = 23,
    Size16M = 24,
    Size1G  = 30
  };
}

namespace RvDataEnums {
  enum eDataMask {
    DwordHi = 0xffffffff00000000,
    DwordLo = 0x00000000ffffffff,
    WordHi  = 0x00000000ffff0000, 
    WordLo  = 0x000000000000ffff,
    HwordHi = 0x000000000000ff00,
    HwordLo = 0x00000000000000ff
    ByteHi  = 0x00000000000000f0
    ByteLo  = 0x000000000000000f
  };
}

#endif
