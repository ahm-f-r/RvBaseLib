#ifndef RV_BASE_FIELD_H
#define RV_BASE_FIELD_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>

#include "RvBaseUtils.h"

using namespace std;
template < typename T > class RvBaseField {
  private :
    static uint64_t mRefCount;
    bool            mIsSet  {false};
    string          mName   {"UNDEFINED"};    
    T               mValue;

  public :
    // ========================================================================
    explicit RvBaseField(string _name, T _value) : mName (_name) {
    // ========================================================================
      Set(_value);
    }

    // ========================================================================
    ~RvBaseField() {
    // ========================================================================
      --mRefCount;
    }
    
    // ========================================================================
    void Print() const {
    // ========================================================================
      cout << Name() << " : " << Get() << endl;
    }

    // ========================================================================
    void Clear() const {
    // ========================================================================
      mIsSet = false;
      mValue = {};
    }

    // ========================================================================
    void Set(T _value) {
    // ========================================================================
      mValue = _value;
      mIsSet = true;
    }

    // ======================================================================== 
    T Get() const {
    // ========================================================================
      if (mIsSet) return mValue;
      else assert(("Accessing field value when field not set.", false));
    }

    // ========================================================================
    string Name() const {
    // ========================================================================
      return mName;
    }
};
template < typename T > uint64_t RvBaseField<T>::mRefCount = 0;

#endif