#ifndef RV_BASE_STRING_PROPERTY_H
#define RV_BASE_STRING_PROPERTY_H

// #include <iostream>
#include <cstdint>
#include <string>
// #include <cassert>
// #include <vector>
// #include <utility>

#include "RvBaseProperty.h"

using namespace std;

class RvBaseStringProperty : public RvBaseProperty<string>
{
  public: 
    explicit RvBaseStringProperty(string _name, string _value);
    ~RvBaseStringProperty();
};

#endif