#ifndef RV_BASE_ADDR_OBJECT_H
#define RV_BASE_ADDR_OBJECT_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <map>

#include "RvBaseUtils.h"
#include "RvBaseEnums.h"
#include "RvBaseObject.h"

using namespace std;
using namespace RvAddrEnums;

class RvBaseAddrObject : public RvBaseObject {
  private:
    uint64_t                    mAddr;
    RvAddrEnums::AddrType       mAddrType;
    RvAddrEnums::PageSize       mPageSize; 
    RvAddrEnums::CacheLineSize  mCacheLSize;
  
  public:
    // ========================================================================
    explicit RvBaseAddrObject(
      uint64_t                   _addr,
      RvAddrEnums::AddrType      _type    = cPhysical,
      RvAddrEnums::PageSize      _pg_sz   = cSize4k, 
      RvAddrEnums::CacheLineSize _cl_sz   = cSize64B,
      string                     _name    = "RvBaseAddrObject", 
      uint64_t                   _id      = 0,
      RvBaseObject const *       _parent  = nullptr) :
        mAddr       (_addr),
        mAddrType   (_type),
        mPageSize   (_pg_sz),
        mCacheLSize (_cl_sz)
    // ========================================================================
    {
      RvBaseObject(_name, _id, _parent);
    }

    // ========================================================================    
    uint64_t Addr() const
    // ========================================================================
    {
      return mAddr;
    }

    // ========================================================================    
    template <typename T> uint64_t Addr() const
    // ========================================================================
    {
      return mAddr & RvBaseAddrUtils::Mask<T>();
    }

    // ========================================================================    
    template <typename T> uint64_t Offset() const
    // ========================================================================
    {
      return mAddr & RvBaseAddrUtils::Offset<T>();
    }

    // ========================================================================    
    template <typename T> uint64_t Next() const
    // ========================================================================
    {
      return mAddr & RvBaseAddrUtils::Offset<T>();
    }

    // ========================================================================
    void Addr(uint64_t _addr)
    // ========================================================================
    {
      mAddr = _addr;
    }
    
    // // ========================================================================
    // template <typename T> void Property(string _name, T _value)
    // // ========================================================================
    // {
    //   Property<T>(_name, _value);
    // }

    // // ========================================================================
    // template <typename T> optional<T> Property(string _name) const
    // // ========================================================================
    // {
    //   return Get<T>(_name);
    // }
};

#endif