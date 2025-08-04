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
  private :
    sConstObj_t sParent {};
    uint64_t    mId     {};
    string      mName   {};

    map<string, varProp_t> mPropertyPool  {};
    map<string, sObj_t   > mChildObjPool  {};

    static uint64_t mRefCount;

  public :
    explicit RvBaseObject(
      string                          _name, 
      uint64_t                        _id,
      shared_ptr<const RvBaseObject>  _parent = nullptr);
   ~RvBaseObject();
    RvBaseObject(RvBaseObject const & _other);
    RvBaseObject & operator=(RvBaseObject const & _other);
    bool operator==(RvBaseObject const & _other);

    shared_ptr<const RvBaseObject>  Parent() const;
    void  Parent (shared_ptr<const RvBaseObject> _parent);

    uint64_t  Id() const;
    void      Id(uint64_t _id);
    
    string    Name() const;
    void      Name(string _name); 
    
    optional< variant<bool, uint64_t, string> > Property(string _name) const;
    void Property(string _name, variant< bool, uint64_t, string > _value);

    shared_ptr<RvBaseObject> ChildObj(string _name) const;
    void ChildObj(string _name, uint64_t _id);

    string  Scope() const;
    void    ClearPropertyPool();
    void    ClearChildObjPool();
    void    CopyPropertyPool(RvBaseObject const & _other, bool _merge = false);
    void    CopyChildObjPool(RvBaseObject const & _other, bool _merge = false);
};
uint64_t RvBaseObject::mRefCount = 0;

#endif
