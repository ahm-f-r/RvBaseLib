#ifndef RV_BASE_OBJECTS_H
#define RV_BASE_OBJECTS_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <map>

#include "RvBaseEnums.h"
#include "RvBaseProperty.h"
#include "RvBaseUtils.h"

using namespace std;


class RvBaseRegisterObject : public RvBaseObject {
  private:
    uint64_t NumOfFields {};  
  public:
    // ========================================================================
    explicit RvBaseRegisterObject(
      string                _name,
      uint64_t              _id = 0,
      RvBaseObject const *  _parent = nullptr) {
    // ========================================================================
      RvBaseObject(_name, _id, _parent);
    }

    // ========================================================================
    void Field(
      string _name, 
      uint64_t _value, 
      uint8_t _start_bit_index = 0, 
      uint8_t _end_bit_index = 63) {
    // ========================================================================
      map<string, RvBaseRegisterField>::iterator _iter;
      _iter = fields.find(_name);
      if(_iter != fields.end()) {
        _iter->second.Value(_value);
        return;
      }
      _iter = fields.begin();
      fields.insert(
        _iter, 
        std::pair<string, RvBaseRegisterField>(
          _name, 
          RvBaseRegisterField(_name, _value, _start_bit_index, _end_bit_index)
        )
      );
    }

    uint64_t Field(string _name) {
      map<string, RvBaseRegisterField>::iterator _iter;
      _iter = fields.find(_name);
      if(_iter != fields.end()) {
        _iter->second.Value();
        return;
      }
    };
};

#endif