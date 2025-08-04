#include "RvBaseObject.h"

using sBoolProp_t = shared_ptr<RvBaseBoolProperty>;
using sStrProp_t  = shared_ptr<RvBaseStringProperty>;
using sUIntProp_t = shared_ptr<RvBaseUInt64Property>;
using sConstObj_t = shared_ptr<const RvBaseObject>;
using sObj_t      = shared_ptr<RvBaseObject>;
using vProp_t     = variant<shared_ptr<RvBaseBoolProperty>,
                            shared_ptr<RvBaseStringProperty>,
                            shared_ptr<RvBaseUInt64Property> >;
using vValue_t    = variant<bool, uint64_t, string>;

// ========================================================================
explicit RvBaseObject::RvBaseObject(
  string      _name   = "Undefined", 
  uint64_t    _id     = 0,
  sConstObj_t _parent = nullptr) :
    sParent (_parent),
    mId     (_id),
    mName   (_name)
// ========================================================================
{
  ++mRefCount;
}

// ========================================================================
RvBaseObject::~RvBaseObject()
// ========================================================================
{
  --mRefCount;
}

// ========================================================================
RvBaseObject::RvBaseObject(RvBaseObject const & _other) :
  sParent (_other.Parent()),
  mId     (_other.Id()),
  mName   (_other.Name())
// ========================================================================
{
  // Note: Existing entries in the pool will be cleared.
  CopyChildObjPool(_other);
  CopyPropertyPool(_other);
}

// ========================================================================
RvBaseObject::RvBaseObject & operator=(RvBaseObject const & _other)
// ========================================================================
{
  Parent(_other.Parent());
  Id(_other.Id());
  Name(_other.Name());
  // Note: Existing entries in the pool will be cleared.
  CopyChildObjPool(_other);
  CopyPropertyPool(_other);
  return *this;
}

// ========================================================================
bool RvBaseObject::operator==(RvBaseObject const & _other) 
// ========================================================================
{
  return this == &(_other);
}

// Methods to access members
// ========================================================================
sConstObj_t RvBaseObject::Parent() const
// ========================================================================
{
  return sParent;
}

// ========================================================================
void RvBaseObject::Parent (sConstObj_t _parent)
// ========================================================================
{
  sParent = _parent;
}

// ========================================================================
uint64_t RvBaseObject::Id() const 
// ========================================================================
{
  return mId;
}

// ========================================================================
void RvBaseObject::Id(uint64_t _id) 
// ========================================================================
{
  mId = _id;
}

// ========================================================================
string RvBaseObject::Name() const 
// ========================================================================
{
  return mName;
}

// ========================================================================
void RvBaseObject::Name(string _name) 
// ========================================================================
{
  mName = _name;
}

// Methods to access Properties and Child Objects
// ========================================================================
optional<vValue_t> RvBaseObject::Property(string _name) const
// ========================================================================
{
  auto const & it = mPropertyPool.find(_name);
  if (it == mPropertyPool.end()) {
    return nullopt;
  }
  if (holds_alternative<sBoolProp_t>(it->second)) {
    auto result = get<sBoolProp_t>(it->second);
    vValue_t prop = result->Value();
    return make_optional(prop);
  }
  if (holds_alternative<sStrProp_t>(it->second)) {
    auto result = get<sStrProp_t>(it->second);
    vValue_t prop = result->Value();
    return make_optional(prop);
  }
  if (holds_alternative<sUIntProp_t>(it->second)) {
    auto result = get<sUIntProp_t>(it->second);
    vValue_t prop = result->Value();
    return make_optional(prop);
  }
  return nullopt;
}

// ========================================================================
void RvBaseObject::Property(string _name, vValue_t _value)
// ========================================================================
{
  bool is_bool_prop = holds_alternative<bool>(_value);
  bool is_uint_prop = holds_alternative<uint64_t>(_value);
  bool is_char_prop = holds_alternative<string>(_value);

  if (Property(_name).has_value()) { 
    if (is_bool_prop) {
      if (holds_alternative<bool>(Property(_name).value())) {
        auto sptr_prop = get<sBoolProp_t>(mPropertyPool[_name]);
        sptr_prop->Value(get<bool>(_value));
        return;
      }
    }
    if (is_uint_prop) {
      if (holds_alternative<uint64_t>(Property(_name).value())) {
        auto sptr_prop = get<sUIntProp_t>(mPropertyPool[_name]);
        sptr_prop->Value(get<uint64_t>(_value));
        return;
      }
    }
    if (is_char_prop) {
      if (holds_alternative<string>(Property(_name).value())) {
        auto sptr_prop = get<sStrProp_t>(mPropertyPool[_name]);
        sptr_prop->Value(get<string>(_value));
        return;
      }
    }
  }
  vProp_t new_prop;
  if (is_bool_prop) {
    new_prop = make_shared<RvBaseBoolProperty>(_name, get<bool>(_value));
  }
  if (is_uint_prop) {
    new_prop = make_shared<RvBaseUInt64Property>(_name, get<uint64_t>(_value));
  }
  if (is_char_prop) {
    new_prop = make_shared<RvBaseStringProperty>(_name, get<string>(_value));
  }
  cout << (get<sStrProp_t>(new_prop))->Name() << endl;
  cout << (get<sStrProp_t>(new_prop))->Value() << endl;
  mPropertyPool.insert(make_pair(_name, new_prop));
  cout << get<sStrProp_t>(mPropertyPool[_name])->Value() << endl;
}

// ========================================================================
sObj_t RvBaseObject::ChildObj(string _name) const
// ========================================================================
{
  auto const & it = mChildObjPool.find(_name);
  if (it == mChildObjPool.end()) {
    return sObj_t(nullptr);
  }
  return it->second;;
}

// ========================================================================
void RvBaseObject::ChildObj(string _name, uint64_t _id)
// ========================================================================
{
  if (ChildObj(_name)) {
    mChildObjPool.erase(_name);
  }
  sObj_t new_child = make_shared<RvBaseObject>(
    _name, 
    _id, 
    make_shared<const RvBaseObject>(*this));
  mChildObjPool[_name] = new_child;
}

// Helper Functions
// ========================================================================
string RvBaseObject::Scope() const
// ========================================================================
{
  if (sParent != nullptr) {
    return (sParent->Scope() + ("." + Name() + "_" + to_string(Id())));
  }
  return string("." + Name() + "_" + to_string(Id()));
}

// ========================================================================
void RvBaseObject::ClearPropertyPool()
// ========================================================================
{
  for (auto & item : mPropertyPool) {
    mPropertyPool.erase(item.first);
  }
}

// ========================================================================
void RvBaseObject::ClearChildObjPool()
// ========================================================================
{
  for (auto & item : mChildObjPool) {
    mChildObjPool.erase(item.first);
  }
}

// ========================================================================
void RvBaseObject::CopyPropertyPool(
  RvBaseObject const & _other, 
  bool _merge = false)
// ========================================================================
{
  if (!_merge) {
    ClearPropertyPool();
  }
  for (auto const & item : _other.mPropertyPool) {
    mPropertyPool[item.first] = item.second;
  }
}

// ========================================================================
void RvBaseObject::CopyChildObjPool(
  RvBaseObject const & _other, 
  bool _merge = false)
// ========================================================================
{
  if (!_merge) {
    ClearChildObjPool();
  }
  for (auto const & item : _other.mChildObjPool) {
    mChildObjPool[item.first] = item.second;
  }
}
