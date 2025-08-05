#include "RvBaseProperty.h"
#include "RvBaseUInt64Property.h"

using namespace std;

// ========================================================================
RvBaseUInt64Property::RvBaseUInt64Property(
  string    _name,
  uint64_t  _value) :
    RvBaseProperty<uint64_t>(_name, _value)
// ========================================================================
{}

// ========================================================================
RvBaseUInt64Property::~RvBaseUInt64Property()
// ========================================================================
{}
