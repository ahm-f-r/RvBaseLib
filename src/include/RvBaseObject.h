#ifndef RV_BASE_OBJECTS_H
#define RV_BASE_OBJECTS_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <map>

#include "RvBaseEnums.h"
#include "RvBaseField.h"
#include "RvBaseUtils.h"

using namespace std;

class RvBaseObject {
  private :
    RvBaseObject const * mParent    {nullptr};
    uint64_t             mId        {};
    string               mName      {};
    map<string, void *>  mFields    {};
    static uint64_t      mRefCount;

  public :
    // ========================================================================
    explicit RvBaseObject(
      string _name = "RvBaseObject", 
      uint64_t _id = 0, 
      RvBaseObject const * _parent = nullptr) {
    // ========================================================================
      Parent(_parent);
      Name(_name);
      Id(_id);
      mRefCount++;
    }

    // ========================================================================
    ~RvBaseObject() {
    // ========================================================================
      for (auto & item : mFields) {
        mFields.erase(item.first);
      }
      --mRefCount;
    }

    // ========================================================================
    RvBaseObject(RvBaseObject const & _other) {
    // ========================================================================
      Parent(_other.Parent());
      Name(_other.Name());
      Id(_other.Id());
      Fields(_other);
    }
    // ========================================================================
    // Move Constructor
    // ========================================================================

    // ========================================================================
    RvBaseObject & operator=(RvBaseObject const & _other) {
    // ========================================================================
      Parent(_other.Parent());
      Name(_other.Name());
      Id(_other.Id());
      Fields(_other);
      return *this;
    }

    // ========================================================================
    bool operator==(RvBaseObject const & other) {
    // ========================================================================
      return (other.Name() == Name()) and 
        other.Scope() == Scope();
    }

    // ========================================================================
    RvBaseObject const * Parent() const {
    // ========================================================================
      return mParent;
    }

    // ========================================================================
    void Parent (RvBaseObject const * _parent) {
    // ========================================================================
      mParent = _parent;
    }

    // ========================================================================
    uint64_t Id() const {
    // ========================================================================
      return mId;
    }

    // ========================================================================
    void Id(uint64_t _id) {
    // ========================================================================
      mId = _id;
    }

    // ========================================================================
    string Name() const {
    // ========================================================================
      return mName;
    }

    // ========================================================================
    void Name(string _name) {
    // ========================================================================
      mName = _name;
    }

    // ========================================================================
    string Scope(uint64_t const _level = 0) const {
    // ========================================================================
      uint64_t level {_level};
      if (mParent) {
        return (mParent->Scope(++level) + ( _level == 0 ? "" : "/" + Name()));
      }
      if (level > 0) {
        return string("$root");
      }
      return string("-----");
    }

    // ========================================================================
    map<string, void *> Fields() const {
    // ========================================================================
      return mFields;
    }

    // ========================================================================
    void CopyFields(RvBaseObject const & other) {
    // ========================================================================
      for (auto & item : mFields) {
        mFields.erase(item.first);
      }
      for (auto & item : other.Fields()) {
        mFields[item.first] = item.second;
      }
    }

    // ========================================================================
    template <typename T> optional<T> Field(string _field_name) const {
    // ========================================================================
      auto const & it = mFields.find(_field_name);
      if (it == mFields.end()) {
        return nullopt;
      }
      RvBaseField<T> * result = static_cast<RvBaseField<T>*>(it->second);
      //cout << "Found: " << result->Name() 
      //     << ", Old Value: " << result->Get() 
      //     << endl;
      return make_optional(result->Get());
    }

    // ========================================================================
    template <typename T> void Field(string _field_name, T _field_value) {
    // ========================================================================
      if (Field<T>(_field_name).has_value()) {
        RvBaseField<T> * result = static_cast<RvBaseField<T>*>(mFields[_field_name]);
        result->Set(_field_value);
        //cout << "Found: " << result->Name() 
        //     << ", New Value: " << result->Get() 
        //     << endl;
        return;
      }
      RvBaseField<T> * newField = new RvBaseField<T>( _field_name, _field_value );
      mFields[_field_name] = newField;
      //cout << "Spawn: " << newField->Name() 
      //     << ", New Value: " << newField->Get() 
      //     << endl;
    }
};
uint64_t RvBaseObject::mRefCount = 0;

#endif