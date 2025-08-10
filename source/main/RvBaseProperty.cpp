#include "RvBaseProperty.h"

using namespace std;

TEMPLATE_t uint64_t RvBaseProperty<T>::mRefCount = 0;

// ========================================================================
TEMPLATE_t RvBaseProperty<T>::RvBaseProperty(
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
TEMPLATE_t RvBaseProperty<T>::~RvBaseProperty()
// ========================================================================
{
  --mRefCount;
}

// ========================================================================
TEMPLATE_t RvBaseProperty<T>::RvBaseProperty(RvBaseProperty const & _other)
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
TEMPLATE_t RvBaseProperty<T> & RvBaseProperty<T>::operator=(RvBaseProperty const & _other)
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
TEMPLATE_t bool RvBaseProperty<T>::operator==(RvBaseProperty const & _other) 
// ========================================================================
{
  // TODO: Check T == {int, uint8_t, uint32_t, uint64_t, string, bool}
  return (Name() == _other.Name()) and (Value() == _other.Value());
}

// Methods to access members
// ========================================================================
TEMPLATE_t string RvBaseProperty<T>::Name() const
// ========================================================================
{
  return mName;
}

// ========================================================================
TEMPLATE_t void RvBaseProperty<T>::Name(string _name)
// ========================================================================
{
  mName = _name;
}

// ========================================================================
TEMPLATE_t void RvBaseProperty<T>::Value(T _value) 
// ========================================================================
{
  mValue = _value;
  SetValid();
}

// ======================================================================== 
TEMPLATE_t T RvBaseProperty<T>::Value() const
// ========================================================================
{
  if (IsValid()) return mValue;
  cout << "[Error] Value() called with no prior initialization." << endl;
  assert(false);
}

// Helper Function
// ========================================================================
TEMPLATE_t uint64_t RvBaseProperty<T>::RefCount() const 
// ========================================================================
{
  return RvBaseProperty<T>::mRefCount;
}

// ========================================================================
TEMPLATE_t string RvBaseProperty<T>::AsString() const 
// ========================================================================
{
  return ("NoImplementation"); //(Name() + " : " + Value());
}

// ========================================================================
TEMPLATE_t void RvBaseProperty<T>::ClearValid()
// ========================================================================
{
  mValid = false;
}

// ========================================================================
TEMPLATE_t void RvBaseProperty<T>::SetValid()
// ========================================================================
{
  mValid = true;
}

// ========================================================================
TEMPLATE_t bool RvBaseProperty<T>::IsValid() const
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
