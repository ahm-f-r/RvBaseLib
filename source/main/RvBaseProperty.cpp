#include "RvBaseProperty.h"

using namespace std;

template <typename T> uint64_t RvBaseProperty<T>::mBasePropertyRefCount = 0;

// ========================================================================
template <typename T> RvBaseProperty<T>::RvBaseProperty(
  string  _name,
  T       _value) :
    mName   (_name),
    mValue  (_value)
// ========================================================================
{
  SetValid();
  ++mBasePropertyRefCount;
}

// ========================================================================
template <typename T> RvBaseProperty<T>::~RvBaseProperty()
// ========================================================================
{
  --mBasePropertyRefCount;
}

// ========================================================================
template <typename T> RvBaseProperty<T>::RvBaseProperty(RvBaseProperty const & _other)
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
template <typename T> RvBaseProperty<T> & RvBaseProperty<T>::operator=(RvBaseProperty const & _other)
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
template <typename T> bool RvBaseProperty<T>::operator==(RvBaseProperty const & _other) 
// ========================================================================
{
  if (!dynamic_cast<T>(_other.Value())) {
    return false;
  }
  return (Name() == _other.Name()) and (Value() == _other.Value());
}

// Methods to access members
// ========================================================================
template <typename T> string RvBaseProperty<T>::Name() const
// ========================================================================
{
  return mName;
}

// ========================================================================
template <typename T> void RvBaseProperty<T>::Name(string _name)
// ========================================================================
{
  mName = _name;
}

// ========================================================================
template <typename T> void RvBaseProperty<T>::Value(T _value) 
// ========================================================================
{
  mValue = _value;
  SetValid();
}

// ======================================================================== 
template <typename T> T RvBaseProperty<T>::Value() const
// ========================================================================
{
  if (IsValid()) return mValue;
  else assert(("Value() called with no prior initialization.", false));
}

// Helper Function
// ========================================================================
template <typename T> void RvBaseProperty<T>::Print() const 
// ========================================================================
{
  cout << Name() << " : " << Value() << endl;
}

// ========================================================================
template <typename T> void RvBaseProperty<T>::ClearValid()
// ========================================================================
{
  mValid = false;
}

// ========================================================================
template <typename T> void RvBaseProperty<T>::SetValid()
// ========================================================================
{
  mValid = true;
}

// ========================================================================
template <typename T> bool RvBaseProperty<T>::IsValid() const
// ========================================================================
{
  return mValid;
}


// // ========================================================================
// RvBaseBoolProperty::RvBaseBoolProperty(
//   string    _name,
//   bool      _value) :
//     RvBaseProperty<bool>(_name, _value)
// // ========================================================================
// {}

// // ========================================================================
// RvBaseBoolProperty::~RvBaseBoolProperty()
// // ========================================================================
// {}


// // ========================================================================
// RvBaseUInt64Property::RvBaseUInt64Property(
//   string    _name,
//   uint64_t  _value) :
//     RvBaseProperty<uint64_t>(_name, _value)
// // ========================================================================
// {}

// // ========================================================================
// RvBaseUInt64Property::~RvBaseUInt64Property()
// // ========================================================================
// {}


// // ========================================================================
// RvBaseStringProperty::RvBaseStringProperty(
//   string  _name,
//   string  _value) :
//     RvBaseProperty<string>(_name, _value)
// // ========================================================================
// {}

// // ========================================================================
// RvBaseStringProperty::~RvBaseStringProperty()
// // ========================================================================
// {}
