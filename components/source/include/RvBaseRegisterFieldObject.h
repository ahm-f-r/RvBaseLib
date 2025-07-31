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
#include "RvBaseField.h"
#include "RvBaseUtils.h"

using namespace std;

class RvBaseRegisterFieldObject : public RvBaseObject {
  private:
    uint64_t  mData {0};

  public:
    // ========================================================================
    explicit RvBaseRegisterFieldObject(
      uint64_t              _data,
      uint8_t               _start_bit_index, 
      uint8_t               _end_bit_index,
      string                _name,
      uint64_t              _id     = 0,
      RvBaseObject const *  _parent = nullptr) : 
        mData(_data) {
    // ========================================================================
      RvBaseObject(_name , _id, _parent);
      Property<uint64_t>("StartBitIndex", _start_bit_index);
      Property<uint64_t>("EndBitIndex", _end_bit_index);
    }

    // ========================================================================
    ~RvBaseRegisterFieldObject() {
    // ========================================================================
    }

    // ========================================================================
    uint64_t Data(bool _start_bit_index_aligned = false) const {
    // ========================================================================
      return _start_bit_index_aligned ? (mData << Property<uint64_t>("StartBitIndex")) : mData;
    }

    // ========================================================================
    void Data(uint64_t _data) {
    // ========================================================================
      mData = _data;
    }

    // ========================================================================
    template <typename T> void Property(string _name, T _value) {
    // ========================================================================
      Field<T>(_name, _value);
    }

    // ========================================================================
    template <typename T> optional<T> Property(string _name) const {
    // ========================================================================
      return Field<T>(_name).has_value() ? Field<T>(_name).value() : 0;
    }
};

#endif