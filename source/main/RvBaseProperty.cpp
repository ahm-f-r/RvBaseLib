#include "RvBaseProperty.h"

using namespace std;

template <typename T> uint64_t RvBaseProperty<T>::mRefCount = 0;

// ========================================================================
template <typename T> RvBaseProperty<T>::RvBaseProperty(
  string  _name,
  T       _value) :
    mName   (_name),
    mValue  (_value)
// ========================================================================
{
  SetValid();
  ++mRefCount;
}

// ========================================================================
template <typename T> RvBaseProperty<T>::~RvBaseProperty()
// ========================================================================
{
  --mRefCount;
}

// ========================================================================
template <typename T> RvBaseProperty<T>::RvBaseProperty(RvBaseProperty const & _other)
// ========================================================================
{
  // TODO: Check T == {int, uint8_t, uint32_t, uint64_t, string, bool}
  Name    ( _other.Name()     );
  Value   ( _other.Value()    );
  ++mRefCount;
  return;

  cout << "[Error] Type mismatch. Aborting." << endl;
  assert(false);
}

// ========================================================================
template <typename T> RvBaseProperty<T> & RvBaseProperty<T>::operator=(RvBaseProperty const & _other)
// ========================================================================
{
  // TODO: Check T == {int, uint8_t, uint32_t, uint64_t, string, bool}
  Name    ( _other.Name()   );
  Value   ( _other.Value()  );
  return *this;

  cout << "[Error] Type mismatch. Aborting." << endl;
  assert(false);
}

// ========================================================================
template <typename T> bool RvBaseProperty<T>::operator==(RvBaseProperty const & _other) 
// ========================================================================
{
  // TODO: Check T == {int, uint8_t, uint32_t, uint64_t, string, bool}
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
  cout << "[Error] Value() called with no prior initialization." << endl;
  assert(false);
}

// Helper Function
// ========================================================================
template <typename T> uint64_t RvBaseProperty<T>::RefCount() const 
// ========================================================================
{
  return RvBaseProperty<T>::mRefCount;
}

// ========================================================================
template <typename T> void RvBaseProperty<T>::Print() const 
// ========================================================================
{
  cout << Name() << " = " << Value() << endl;
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

// ========================================================================
// Note:
// ========================================================================
// * Only basic datatypes are supported by default.
// * See examples on how user data types can be implemented.
template class RvBaseProperty<bool>;
template class RvBaseProperty<string>;
template class RvBaseProperty<uint64_t>;
