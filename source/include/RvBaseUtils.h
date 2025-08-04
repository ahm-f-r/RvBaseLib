#ifndef RV_BASE_UTILS_H
#define RV_BASE_UTILS_H

#include <iostream>
#include <string>

#include "RvBaseEnums.h"

using namespace std;

namespace RvBaseAddrUtils {

  template<typename T> uint64_t Mask(T _size) {
    return ~((1ull << _size)-1);
  }

  template <typename T> uint64_t Offset(T _size) {
    return ((1ull << _size)-1);
  }

  template <typename T> uint64_t Next(T _size, uint64_t _addr) {
    return ((Mask<T>(_size) & _addr) + (1ull << _size));
  }

  template <typename T> bool IsCrossing(T _size, uint64_t _addr, uint64_t _increment) {
    return ((_addr + _increment) & Mask<T>(_size)) == Next<T>(_size, _addr);
  }

  template <typename T> bool IsPresent(T _size, uint64_t _addr) {
    return (_addr & Mask<T>(_size)) == Mask(_size);
  }
}

namespace RvBaseDataUtils {

}

#endif
