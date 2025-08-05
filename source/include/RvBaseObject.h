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
#include "RvBaseBoolProperty.h"
#include "RvBaseStringProperty.h"
#include "RvBaseUInt64Property.h"

using namespace std;

class RvBaseObject {
  //using shared_ptr<const RvBaseObject> = shared_ptr<const RvBaseObject>;
  // using sObj_t      = shared_ptr<RvBaseObject>;
  // using vProp_t     = variant<shared_ptr<RvBaseBoolProperty>,
  //                             shared_ptr<RvBaseStringProperty>,
  //                             shared_ptr<RvBaseUInt64Property> >;
  //using sBoolProp_t = shared_ptr<RvBaseBoolProperty>;
  // using sStrProp_t  = shared_ptr<RvBaseStringProperty>;
  // using sUIntProp_t = shared_ptr<RvBaseUInt64Property>;
  // using vValue_t    = variant<bool, uint64_t, string>;

  private :
    /*shared_ptr<const RvBaseObject>*/ shared_ptr<const RvBaseObject> sParent {};
    uint64_t                  mId     {};
    string                    mName   {};

    map<
      string, 
      variant<
        shared_ptr<RvBaseBoolProperty>,
        shared_ptr<RvBaseStringProperty>,
        shared_ptr<RvBaseUInt64Property>
      > 
      /* vProp_t */
    > mPropertyPool {};

    map<
      string, 
      // sObj_t
      shared_ptr<RvBaseObject>
    > mChildObjPool  {};

    static uint64_t mBaseObjectRefCount;

  public :
    explicit RvBaseObject(
      string                          _name, 
      uint64_t                        _id,
      /*shared_ptr<const RvBaseObject>*/ shared_ptr<const RvBaseObject> _parent = nullptr);
   ~RvBaseObject();
    RvBaseObject(RvBaseObject const & _other);
    RvBaseObject & operator=(RvBaseObject const & _other);
    bool operator==(RvBaseObject const & _other);

    shared_ptr<const RvBaseObject> Parent() const;
    void Parent(/*shared_ptr<const RvBaseObject>*/ shared_ptr<const RvBaseObject> _parent);

    uint64_t  Id() const;
    void      Id(uint64_t _id);

    string    Name() const;
    void      Name(string _name); 

    optional< /*vValue_t */ variant<bool, string, uint64_t> > Property(string _name) const;
    void Property(string _name, /*vValue_t*/ variant<bool, string, uint64_t> _value);

    shared_ptr<RvBaseObject> ChildObj(string _name) const;
    void ChildObj(string _name, uint64_t _id);

    string  Scope() const;
    void    ClearPropertyPool();
    void    ClearChildObjPool();
    void    CopyPropertyPool(RvBaseObject const & _other, bool _merge = false);
    void    CopyChildObjPool(RvBaseObject const & _other, bool _merge = false);
};

#endif
