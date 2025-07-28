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

// Register Objects

class RvBaseRegisterObject : public RvBaseObject {
  private:
    uint64_t NumOfFields {};  
  public:
    // ========================================================================
    explicit RvBaseRegisterObject(
      string                _name,
      uint64_t              _id = 0,
      RvBaseObject const *  _parent = nullptr) {
    // ========================================================================
      RvBaseObject(_name, _id, _parent);
    }

    // ========================================================================
    void Field(
      string _name, 
      uint64_t _value, 
      uint8_t _start_bit_index = 0, 
      uint8_t _end_bit_index = 63) {
    // ========================================================================
      map<string, RvBaseRegisterField>::iterator _iter;
      _iter = fields.find(_name);
      if(_iter != fields.end()) {
        _iter->second.Value(_value);
        return;
      }
      _iter = fields.begin();
      fields.insert(
        _iter, 
        std::pair<string, RvBaseRegisterField>(
          _name, 
          RvBaseRegisterField(_name, _value, _start_bit_index, _end_bit_index)
        )
      );
    }

    uint64_t Field(string _name) {
      map<string, RvBaseRegisterField>::iterator _iter;
      _iter = fields.find(_name);
      if(_iter != fields.end()) {
        _iter->second.Value();
        return;
      }
    };
};

class RvBaseRegisterFieldObject : public RvBaseObject {
  private:
    uint64_t  mData {0};

  public:
    // ========================================================================
    explicit RvBaseRegisterFieldObject(
      uint64_t              _data,
      uint8_t               _start_bit_index, 
      uint8_t               _end_bit_index,
      string                _name,
      uint64_t              _id     = 0,
      RvBaseObject const *  _parent = nullptr) : 
        mData(_data) {
    // ========================================================================
      RvBaseObject(_name , _id, _parent);
      Property<uint64_t>("StartBitIndex", _start_bit_index);
      Property<uint64_t>("EndBitIndex", _end_bit_index);
    }

    // ========================================================================
    ~RvBaseRegisterFieldObject() {
    // ========================================================================
    }

    // ========================================================================
    uint64_t Data(bool _start_bit_index_aligned = false) const {
    // ========================================================================
      return _start_bit_index_aligned ? (mData << Property<uint64_t>("StartBitIndex")) : mData;
    }

    // ========================================================================
    void Data(uint64_t _data) {
    // ========================================================================
      mData = _data;
    }

    // ========================================================================
    template <typename T> void Property(string _name, T _value) {
    // ========================================================================
      Field<T>(_name, _value);
    }

    // ========================================================================
    template <typename T> optional<T> Property(string _name) const {
    // ========================================================================
      return Field<T>(_name).has_value() ? Field<T>(_name).value() : 0;
    }
};

// Base, Addr, Data Objects

class RvBaseAddrObject : public RvBaseObject {
  private:
    uint64_t mAddr {0};
  
  public:
    // ========================================================================
    explicit RvBaseAddrObject(
      uint64_t              _addr,
      string                _name = "RvBaseAddrObject", 
      uint64_t              _id = 0,
      RvBaseObject const *  _parent = nullptr) : mAddr (_addr) {
    // ========================================================================
      RvBaseObject(_name, _id, _parent);
    }
 
    // ========================================================================    
    uint64_t Addr() const {
    // ========================================================================
      return mAddr;
    }

    // ========================================================================    
    template <typename T> uint64_t Addr() const {
    // ========================================================================
      return mAddr & RvBaseAddrUtils::Mask<T>();
    }

    // ========================================================================
    void Addr(uint64_t _addr) {
    // ========================================================================
      mAddr = _addr;
    }
};

class RvBaseDataObject : public RvBaseObject {
  private:
    uint8_t mData {0};
    bool    mMask {false};

  public:
    // ========================================================================
    explicit RvBaseDataObject(
      uint8_t               _data,
      bool                  _mask,
      string                _name = "RvBaseDataObject", 
      uint64_t              _id = 0,
      RvBaseObject const *  _parent = nullptr) : 
        mData(_data),
        mMask(_mask) {
    // ========================================================================
      RvBaseObject(_name , _id, _parent);
    }

    // ========================================================================
    ~RvBaseDataObject() {
    // ========================================================================
    }

    // ========================================================================
    uint8_t Data() const {
    // ========================================================================
      return mMask ? mData : 0;
    }

    // ========================================================================
    void Data(uint8_t _data, bool _mask = true) {
    // ========================================================================
      mData = _data;
      mMask = _mask;
    }

    // ========================================================================
    template <typename T> void SetProperty(string _name, T _value) {
    // ========================================================================
      Set<T>(_name, _value);
    }

    // ========================================================================
    template <typename T> optional<T> GetProperty(string _name) const {
    // ========================================================================
      return Get<T>(_name);
    }
};

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
        delete item.second;
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
    void Fields(RvBaseObject const & other) {
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