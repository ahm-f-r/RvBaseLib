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
#include "RvBaseUtils.h"
#include "RvBaseObject.h"
#include "RvBaseProperty.h"

using namespace std;

class RvBaseDataObject : public RvBaseObject {
  private:
    uint8_t mData {};
    bool    mMask {};

  public:
    // ========================================================================
    explicit RvBaseDataObject(
      uint8_t               _data,
      bool                  _mask,
      string                _name = "RvBaseDataObject", 
      uint64_t              _id = 0,
      shared_ptr<RvBaseObject const *  _parent = nullptr) : 
        mData(_data),
        mMask(_mask) {
    // ========================================================================
      RvBaseObject(_name , _id, _parent);
    }

    // ========================================================================
    ~RvBaseDataObject() {
    // ========================================================================
    }

    // ========================================================================
    uint8_t Data() const {
    // ========================================================================
      return mMask ? mData : 0;
    }

    // ========================================================================
    void Data(uint8_t _data, bool _mask = true) {
    // ========================================================================
      mData = _data;
      mMask = _mask;
    }

    // ========================================================================
    TEMPLATE_t void SetProperty(string _name, T _value) {
    // ========================================================================
      Set<T>(_name, _value);
    }

    // ========================================================================
    TEMPLATE_t optional<T> GetProperty(string _name) const {
    // ========================================================================
      return Get<T>(_name);
    }
};

#endif