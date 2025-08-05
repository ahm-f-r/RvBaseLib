#include "RvBaseProperty.h"
#include "RvBaseBoolProperty.h"

using namespace std;

// ========================================================================
RvBaseBoolProperty::RvBaseBoolProperty(
  string    _name,
  bool      _value) :
    RvBaseProperty<bool>(_name, _value)
// ========================================================================
{}

// ========================================================================
RvBaseBoolProperty::~RvBaseBoolProperty()
// ========================================================================
{}
