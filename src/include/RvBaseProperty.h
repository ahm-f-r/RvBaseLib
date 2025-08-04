#ifndef RV_BASE_PROPERTY_H
#define RV_BASE_PROPERTY_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>

#include "RvBaseUtils.h"
#include "RvBaseEnums.h"

using namespace std;

template <typename T> class RvBaseProperty
{
  private :
    string                          mName {"Undefined"};    
    T                               mValue;
    bool                            mValid {false};
    static uint64_t                 mRefCount;

  public :
    // ========================================================================
    explicit RvBaseProperty(
      string                          _name,
      T                               _value) :
        mName   (_name),
        mValue  (_value)
    // ========================================================================
    {
      SetValid();
      ++mRefCount;
    }

    // ========================================================================
    ~RvBaseProperty()
    // ========================================================================
    {
      --mRefCount;
    }

    // ========================================================================
    RvBaseProperty(RvBaseProperty const & _other)
    // ========================================================================
    {
      if (dynamic_cast<T>(_other.Value())) {
        Name    ( _other.Name()     );
        Value   ( _other.Value()    );
        return;
      }
      assert(("Type mismatch. Aborting.", false));
    }

    // ========================================================================
    RvBaseProperty & operator=(RvBaseProperty const & _other)
    // ========================================================================
    {
      if (dynamic_cast<T>(_other.Value())) {
        Name    ( _other.Name()   );
        Value   ( _other.Value()  );
        return *this;
      }
      assert(("Type mismatch. Aborting.", false));
    }

    // ========================================================================
    bool operator==(RvBaseProperty const & _other) 
    // ========================================================================
    {
      if (!dynamic_cast<T>(_other.Value())) {
        return false;
      }
      return (Name() == _other.Name()) and (Value() == _other.Value());
    }

    // Methods to access members
    // ========================================================================
    string Name() const
    // ========================================================================
    {
      return mName;
    }

    // ========================================================================
    void Name(string _name)
    // ========================================================================
    {
      mName = _name;
    }

    // ========================================================================
    void Value(T _value) 
    // ========================================================================
    {
      mValue = _value;
      SetValid();
    }

    // ======================================================================== 
    T Value() const
    // ========================================================================
    {
      if (IsValid()) return mValue;
      else assert(("Value() called without any prior initialization.", false));
    }

    // Helper Function
    // ========================================================================
    void Print() const 
    // ========================================================================
    {
      cout << Name() << " : " << Value() << endl;
    }

    // ========================================================================
    void ClearValid()
    // ========================================================================
    {
      mValid = false;
    }

    // ========================================================================
    void SetValid()
    // ========================================================================
    {
      mValid = true;
    }

    // ========================================================================
    bool IsValid() const
    // ========================================================================
    {
      return mValid;
    } 
};
template < typename T > uint64_t RvBaseProperty<T>::mRefCount = 0;

class RvBaseBoolProperty : public RvBaseProperty<bool> {
  public:
    // ========================================================================
    explicit RvBaseBoolProperty(
      string                          _name,
      bool                            _value) :
        RvBaseProperty<bool>(_name, _value)
    // ========================================================================
    {}
};

class RvBaseUInt64Property : public RvBaseProperty<uint64_t> {
  public:
    // ========================================================================
    explicit RvBaseUInt64Property(
      string                          _name,
      uint64_t                        _value) :
        RvBaseProperty<uint64_t>(_name, _value)
    // ========================================================================
    {}
};

class RvBaseStringProperty : public RvBaseProperty<string> {
  public: 
    // ========================================================================
    explicit RvBaseStringProperty(
      string                          _name,
      string                          _value) :
        RvBaseProperty<string>(_name, _value)
    // ========================================================================
    {}
};

#endif