#ifndef RV_BASE_BOOL_PROPERTY_H
#define RV_BASE_BOOL_PROPERTY_H

// #include <iostream>
#include <cstdint>
#include <string>
// #include <cassert>
// #include <vector>
// #include <utility>

#include "RvBaseProperty.h"

using namespace std;

class RvBaseBoolProperty : public RvBaseProperty<bool>
{
  public:
    explicit RvBaseBoolProperty(string _name, bool _value);
    ~RvBaseBoolProperty();
};

#endif