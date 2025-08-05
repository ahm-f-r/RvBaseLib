#include "RvBaseProperty.h"
#include "RvBaseStringProperty.h"

using namespace std;

// ========================================================================
RvBaseStringProperty::RvBaseStringProperty(
  string  _name,
  string  _value) :
    RvBaseProperty<string>(_name, _value)
// ========================================================================
{}

// ========================================================================
RvBaseStringProperty::~RvBaseStringProperty()
// ========================================================================
{}
