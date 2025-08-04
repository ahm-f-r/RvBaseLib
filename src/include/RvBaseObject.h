#ifndef RV_BASE_OBJECTS_H
#define RV_BASE_OBJECTS_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <map>
#include <memory>
#include <optional>
#include <variant>

#include "RvBaseEnums.h"
#include "RvBaseUtils.h"
#include "RvBaseProperty.h"

using namespace std;

class RvBaseObject {
  
  using sBoolProp_t = shared_ptr<RvBaseBoolProperty>;
  using sStrProp_t  = shared_ptr<RvBaseStringProperty>;
  using sUIntProp_t = shared_ptr<RvBaseUInt64Property>;
  using varProp_t   = variant<sBoolProp_t, sStrProp_t, sUIntProp_t>;

  using sConstObj_t = shared_ptr<const RvBaseObject>;
  using sObj_t      = shared_ptr<RvBaseObject>;

  using varValue_t  = variant<bool, uint64_t, string>;

  private :
    sConstObj_t sParent {};
    uint64_t    mId     {};
    string      mName   {};

    map<string, varProp_t> mPropertyPool  {};
    map<string, sObj_t   > mChildObjPool  {};

    static uint64_t mRefCount;

  public :
    // ========================================================================
    explicit RvBaseObject(
      string                          _name   = "Undefined", 
      uint64_t                        _id     = 0,
      shared_ptr<const RvBaseObject>  _parent = nullptr) :
        sParent (_parent),
        mId     (_id),
        mName   (_name)
    // ========================================================================
    {
      ++mRefCount;
    }

    // ========================================================================
    ~RvBaseObject()
    // ========================================================================
    {
      --mRefCount;
    }

    // ========================================================================
    RvBaseObject(RvBaseObject const & _other) :
      sParent (_other.Parent()),
      mId     (_other.Id()),
      mName   (_other.Name())
    // ========================================================================
    {
      // Note: Existing entries in the pool will be cleared.
      CopyChildObjPool(_other);
      CopyPropertyPool(_other);
    }

    // // ========================================================================
    // RvBaseObject(RvBaseObject && _other) :
    //   mParent (_other.Parent()),
    //   mName   (_other.Name()),
    //   mId     (_other.Id())
    // // ========================================================================
    // {
    //   _other.Parent(nullptr);
    //   _other.Name("MovedObject");
    //   _other.Id(0);
      
    //   CopyChildObjPool(_other);
    //   CopyPropertyPool(_other);

    //   _other.ClearChildObjPool();
    //   _other.ClearPropertyPool();
    // }

    // ========================================================================
    RvBaseObject & operator=(RvBaseObject const & _other)
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
    bool operator==(RvBaseObject const & _other) 
    // ========================================================================
    {
      return this == &(_other);
    }

    // Methods to access members
    // ========================================================================
    sConstObj_t Parent() const
    // ========================================================================
    {
      return sParent;
    }

    // ========================================================================
    void Parent (sConstObj_t _parent)
    // ========================================================================
    {
      sParent = _parent;
    }

    // ========================================================================
    uint64_t Id() const 
    // ========================================================================
    {
      return mId;
    }

    // ========================================================================
    void Id(uint64_t _id) 
    // ========================================================================
    {
      mId = _id;
    }

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

    // Methods to access Properties and Child Objects
    // ========================================================================
    optional<varValue_t> Property(string _name) const
    // ========================================================================
    {
      auto const & it = mPropertyPool.find(_name);
      if (it == mPropertyPool.end()) {
        return nullopt;
      }
      if (holds_alternative<sBoolProp_t>(it->second)) {
        auto result = get<sBoolProp_t>(it->second);
        varValue_t prop = result->Value();
        return make_optional(prop);
      }
      if (holds_alternative<sStrProp_t>(it->second)) {
        auto result = get<sStrProp_t>(it->second);
        varValue_t prop = result->Value();
        return make_optional(prop);
      }
      if (holds_alternative<sUIntProp_t>(it->second)) {
        auto result = get<sUIntProp_t>(it->second);
        varValue_t prop = result->Value();
        return make_optional(prop);
      }
      return nullopt;
    }

    // ========================================================================
    void Property(string _name, varValue_t _value)
    // ========================================================================
    {
      bool is_bool_prop = holds_alternative<bool>(_value);
      bool is_uint_prop = holds_alternative<uint64_t>(_value);
      bool is_char_prop = holds_alternative<string>(_value);

      if (Property(_name).has_value()) { 
        if (is_bool_prop) {
          if (holds_alternative<bool>(Property(_name).value())) {
            auto sptr_prop = get<shared_ptr<RvBaseBoolProperty> >(mPropertyPool[_name]);
            sptr_prop->Value(get<bool>(_value));
            return;
          }
        }
        if (is_uint_prop) {
          if (holds_alternative<uint64_t>(Property(_name).value())) {
            auto sptr_prop = get<shared_ptr<RvBaseUInt64Property> >(mPropertyPool[_name]);
            sptr_prop->Value(get<uint64_t>(_value));
            return;
          }
        }
        if (is_char_prop) {
          if (holds_alternative<string>(Property(_name).value())) {
            auto sptr_prop = get<shared_ptr<RvBaseStringProperty> >(mPropertyPool[_name]);
            sptr_prop->Value(get<string>(_value));
            return;
          }
        }
      }
      variant<shared_ptr<RvBaseBoolProperty>,
              shared_ptr<RvBaseUInt64Property>,
              shared_ptr<RvBaseStringProperty> > new_prop;
      if (is_bool_prop) {
        new_prop = make_shared<RvBaseBoolProperty>(_name, get<bool>(_value));
      }
      if (is_uint_prop) {
        new_prop = make_shared<RvBaseUInt64Property>(_name, get<uint64_t>(_value));
      }
      if (is_char_prop) {
        new_prop = make_shared<RvBaseStringProperty>(_name, get<string>(_value));
      }
      cout << (get<shared_ptr<RvBaseStringProperty> >(new_prop))->Name() << endl;
      cout << (get<shared_ptr<RvBaseStringProperty> >(new_prop))->Value() << endl;
      mPropertyPool.insert(make_pair(_name, new_prop));
      cout << "here 5" << endl;
      cout << get<shared_ptr<RvBaseStringProperty> >(mPropertyPool[_name])->Value() << endl;
    }

    // ========================================================================
    shared_ptr<RvBaseObject> ChildObj(string _name) const
    // ========================================================================
    {
      auto const & it = mChildObjPool.find(_name);
      if (it == mChildObjPool.end()) {
        return shared_ptr<RvBaseObject>(nullptr);
      }
      return it->second;;
    }

    // ========================================================================
    void ChildObj(string _name, uint64_t _id)
    // ========================================================================
    {
      if (ChildObj(_name)) {
        cout << _name << " " << "Child Obj exists & will be removed." << endl;
        mChildObjPool.erase(_name);
      }
      cout << _name << " " << "New Child Obj created." << endl; 
      shared_ptr<RvBaseObject> new_child = make_shared<RvBaseObject>(_name, _id, make_shared<const RvBaseObject>(*this));
      mChildObjPool[_name] = new_child;
    }

    // Helper Functions
    // ========================================================================
    string Scope() const
    // ========================================================================
    {
      if (sParent != nullptr) {
        return (sParent->Scope() + ("." + Name() + "_" + to_string(Id())));
      }
      return string("." + Name() + "_" + to_string(Id()));
    }

    // ========================================================================
    void ClearPropertyPool()
    // ========================================================================
    {
      for (auto & item : mPropertyPool) {
        mPropertyPool.erase(item.first);
      }
    }

    // ========================================================================
    void ClearChildObjPool()
    // ========================================================================
    {
      for (auto & item : mChildObjPool) {
        mChildObjPool.erase(item.first);
      }
    }

    // ========================================================================
    void CopyPropertyPool(RvBaseObject const & _other, bool _merge = false)
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
    void CopyChildObjPool(RvBaseObject const & _other, bool _merge = false)
    // ========================================================================
    {
      if (!_merge) {
        ClearChildObjPool();
      }
      for (auto const & item : _other.mChildObjPool) {
        mChildObjPool[item.first] = item.second;
      }
    }
};
uint64_t RvBaseObject::mRefCount = 0;

#endif