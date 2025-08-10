#include "RvBaseObject.h"


uint64_t RvBaseObject::mRefCount = 0;

// ========================================================================
RvBaseObject::RvBaseObject(
  string      _name,
  uint64_t    _id,
  shared_ptr<const RvBaseObject> _parent) :
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
  ++mRefCount;
  // Note: Existing entries in the pool will be cleared.
  CopyChildObjPool(_other);
  CopyPropertyPool(_other);
}

// ========================================================================
RvBaseObject & RvBaseObject::operator=(RvBaseObject const & _other)
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
shared_ptr<const RvBaseObject> RvBaseObject::Parent() const
// ========================================================================
{
  return sParent;
}

// ========================================================================
void RvBaseObject::Parent (shared_ptr<const RvBaseObject> _parent)
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
optional<variant<bool, string, uint64_t> > RvBaseObject::Property(string _name) const
// ========================================================================
{
  auto const & it = mPropertyPool.find(_name);
  if (it == mPropertyPool.end()) {
    return nullopt;
  }
  if (holds_alternative<shared_ptr<RvBaseProperty<bool> > >(it->second)) {
    auto result = get<shared_ptr<RvBaseProperty<bool> > >(it->second);
    variant<bool, string, uint64_t> prop = result->Value();
    return make_optional(prop);
  }
  if (holds_alternative<shared_ptr<RvBaseProperty<string> > >(it->second)) {
    auto result = get<shared_ptr<RvBaseProperty<string> > >(it->second);
    variant<bool, string, uint64_t> prop = result->Value();
    return make_optional(prop);
  }
  if (holds_alternative<shared_ptr<RvBaseProperty<uint64_t> > >(it->second)) {
    auto result = get<shared_ptr<RvBaseProperty<uint64_t> > >(it->second);
    variant<bool, string, uint64_t> prop = result->Value();
    return make_optional(prop);
  }
  return nullopt;
}

// ========================================================================
void RvBaseObject::Property(string _name, variant<bool, string, uint64_t> _value)
// ========================================================================
{
  bool is_bool_prop = holds_alternative<bool>(_value);
  bool is_uint_prop = holds_alternative<uint64_t>(_value);
  bool is_char_prop = holds_alternative<string>(_value);

  if (Property(_name).has_value()) {
    if (is_bool_prop) {
      if (holds_alternative<bool>(Property(_name).value())) {
        auto sptr_prop = get<shared_ptr<RvBaseProperty<bool> > >(mPropertyPool[_name]);
        sptr_prop->Value(get<bool>(_value));
        return;
      }
    }
    if (is_uint_prop) {
      if (holds_alternative<uint64_t>(Property(_name).value())) {
        auto sptr_prop = get<shared_ptr<RvBaseProperty<uint64_t> > >(mPropertyPool[_name]);
        sptr_prop->Value(get<uint64_t>(_value));
        return;
      }
    }
    if (is_char_prop) {
      if (holds_alternative<string>(Property(_name).value())) {
        auto sptr_prop = get<shared_ptr<RvBaseProperty<string> > >(mPropertyPool[_name]);
        sptr_prop->Value(get<string>(_value));
        return;
      }
    }
  }
  variant<shared_ptr<RvBaseProperty<bool> >,
          shared_ptr<RvBaseProperty<string> >,
          shared_ptr<RvBaseProperty<uint64_t> > > new_prop;
  if (is_bool_prop) {
    new_prop = make_shared<RvBaseProperty<bool> >(_name, get<bool>(_value));
  }
  if (is_uint_prop) {
    new_prop = make_shared<RvBaseProperty<uint64_t> >(_name, get<uint64_t>(_value));
  }
  if (is_char_prop) {
    new_prop = make_shared<RvBaseProperty<string> >(_name, get<string>(_value));
  }
  mPropertyPool.insert(make_pair(_name, new_prop));
}

// ========================================================================
shared_ptr<RvBaseObject> RvBaseObject::ChildObj(string _name) const
// ========================================================================
{
  auto const & it = mChildObjPool.find(_name);
  if (it == mChildObjPool.end()) {
    return shared_ptr<RvBaseObject>(nullptr);
  }
  return it->second;
}

// ========================================================================
void RvBaseObject::ChildObj(string _name, uint64_t _id)
// ========================================================================
{
  if (ChildObj(_name) and (ChildObj(_name)->Id() == _id)) {
    return;
  }
  shared_ptr<RvBaseObject> new_child = make_shared<RvBaseObject>(
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
  return string(Name() + "_" + to_string(Id()));
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
void RvBaseObject::CopyPropertyPool(RvBaseObject const & _other, bool _merge, bool deep_copy)
// ========================================================================
{
  bool is_bool_prop {false};
  bool is_uint_prop {false};
  bool is_char_prop {false};
  variant<bool, string, uint64_t> new_value;
  if (!_merge) {
    ClearPropertyPool();
  }
  for (auto const & item : _other.mPropertyPool) {
    if (deep_copy) {
      cout << item.first << endl;
      is_bool_prop = _other.Property(item.first).has_value() and holds_alternative<bool>(_other.Property(item.first).value());
      is_uint_prop = _other.Property(item.first).has_value() and holds_alternative<uint64_t>(_other.Property(item.first).value());
      is_char_prop = _other.Property(item.first).has_value() and holds_alternative<string>(_other.Property(item.first).value());
      if (is_bool_prop) {
        new_value = get<bool>(_other.Property(item.first).value());
      }
      if (is_uint_prop) {
        new_value = get<uint64_t>(_other.Property(item.first).value());
      }
      if (is_char_prop) {
        new_value = get<string>(_other.Property(item.first).value());
      }
      Property(item.first, new_value);
      continue;
    }
    // Shallow Copy
    mPropertyPool[item.first] = item.second;
  }
}

// ========================================================================
void RvBaseObject::CopyChildObjPool(RvBaseObject const & _other, bool _merge, bool _deep_copy)
// ========================================================================
{
  if (!_merge) {
    ClearChildObjPool();
  }
  for (auto const & item : _other.mChildObjPool) {
    // Deep Copy
    if (_deep_copy) {
      ChildObj(item.first, item.second->Id());
      ChildObj(item.first)->CopyPropertyPool(*item.second, _merge, _deep_copy);
      continue;
    }
    // Shallow Copy
    mChildObjPool[item.first] = item.second;
  }
}

// ========================================================================
string RvBaseObject::PropsAsString(uint64_t _level) const
// ========================================================================
{
  string   line_body    {};
  string   line_indent  {};
  string   line_end     {"\n"};

  // Setup Indentation
  for (uint64_t i {0}; i < _level; ++i) {
    line_indent += "\t";
  }
  line_body += (line_indent + "+( " + Scope() + " )" + line_end);
  // Print own properties
  for (auto const & item : mPropertyPool) {
    if (Property(item.first).has_value()) {
      string result;
      if (holds_alternative<bool>(Property(item.first).value())) {
        result = to_string(get<bool>(Property(item.first).value()));
      }
      else if (holds_alternative<uint64_t>(Property(item.first).value())) {
        result = to_string(get<uint64_t>(Property(item.first).value()));
      }
      else if (holds_alternative<string>(Property(item.first).value())) {
        result = get<string>(Property(item.first).value());
      }
      line_body += (line_indent + "| " + item.first + " : " + result + line_end);
    }
  }
  return line_body;
}

// ========================================================================
string RvBaseObject::ChildObjsAsString(stack<string> & _str_stack, uint64_t _level) const
// ========================================================================
{
  string    result {""};
  uint64_t  level  {++_level};
  for (auto const & item : mChildObjPool) {
    (item.second->ChildObjsAsString(_str_stack, level));
  }
  _str_stack.push(PropsAsString(_level));

  if ((level-1) == 0) {
    _str_stack.push("\n");
    while(!_str_stack.empty()) {
      result += _str_stack.top();
      _str_stack.pop();
    }
  }
  return result;
}

string RvBaseObject::ObjectHierarchyAsString() const {
  stack<string> str_stack {};
  return ChildObjsAsString(str_stack, 0);
}
