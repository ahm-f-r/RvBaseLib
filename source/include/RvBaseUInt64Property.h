#ifndef RV_BASE_UINT64_PROPERTY_H
#define RV_BASE_UINT64_PROPERTY_H

// #include <iostream>
#include <cstdint>
#include <string>
// #include <cassert>
// #include <vector>
// #include <utility>

#include "RvBaseProperty.h"

using namespace std;

class RvBaseUInt64Property : public RvBaseProperty<uint64_t>
{
  public:
    explicit RvBaseUInt64Property(string _name, uint64_t _value);
    ~RvBaseUInt64Property();
};

#endif