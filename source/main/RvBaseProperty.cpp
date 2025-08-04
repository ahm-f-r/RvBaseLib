#include "RvBaseProperty.h"

using namespace std;

explicit RvBaseProperty::RvBaseProperty(
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
~RvBaseProperty::RvBaseProperty()
// ========================================================================
{
    --mRefCount;
}

// ========================================================================
RvBaseProperty::RvBaseProperty(RvBaseProperty const & _other)
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
RvBaseProperty & RvBaseProperty::operator=(RvBaseProperty const & _other)
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
bool RvBaseProperty::operator==(RvBaseProperty const & _other) 
// ========================================================================
{
    if (!dynamic_cast<T>(_other.Value())) {
    return false;
    }
    return (Name() == _other.Name()) and (Value() == _other.Value());
}

// Methods to access members
// ========================================================================
string RvBaseProperty::Name() const
// ========================================================================
{
    return mName;
}

// ========================================================================
void RvBaseProperty::Name(string _name)
// ========================================================================
{
    mName = _name;
}

// ========================================================================
void RvBaseProperty::Value(T _value) 
// ========================================================================
{
    mValue = _value;
    SetValid();
}

// ======================================================================== 
T RvBaseProperty::Value() const
// ========================================================================
{
    if (IsValid()) return mValue;
    else assert(("Value() called with no prior initialization.", false));
}

// Helper Function
// ========================================================================
void RvBaseProperty::Print() const 
// ========================================================================
{
    cout << Name() << " : " << Value() << endl;
}

// ========================================================================
void RvBaseProperty::ClearValid()
// ========================================================================
{
    mValid = false;
}

// ========================================================================
void RvBaseProperty::SetValid()
// ========================================================================
{
    mValid = true;
}

// ========================================================================
bool RvBaseProperty::IsValid() const
// ========================================================================
{
    return mValid;
} 


// ========================================================================
explicit RvBaseBoolProperty::RvBaseBoolProperty(
  string    _name,
  bool      _value) :
    RvBaseProperty<bool>(_name, _value)
// ========================================================================
{}


// ========================================================================
explicit RvBaseUInt64Property::RvBaseUInt64Property(
  string    _name,
  uint64_t  _value) :
    RvBaseProperty<uint64_t>(_name, _value)
// ========================================================================
{}

// ========================================================================
explicit RvBaseStringProperty::RvBaseStringProperty(
  string  _name,
  string  _value) :
    RvBaseProperty<string>(_name, _value)
// ========================================================================
{}
