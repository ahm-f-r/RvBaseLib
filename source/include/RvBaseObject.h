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
#include <stack>

#include "RvBaseCommon.d"
#include "RvBaseUtils.h"
#include "RvBaseProperty.h"

using namespace std;

class RvBaseObject {
  private :
    SHARED_CONST_OBJ_t              sParent     {};
    uint64_t                        mUniqueId   {};
    string                          mName       {};
    bool                            mRegistered {};

    map<string, SHARED_VARIANT_t>   mPropertyPool   {};
    map<string, SHARED_OBJECT_t >   mChildObjPool   {};
    map<string, SHARED_OBJECT_t >   mExtObjRefPool  {};

    static uint64_t mRefCount;
    static vector<SHARED_OBJECT_t>  mGlobalRefPool;

  public :
    explicit RvBaseObject(
      string              _name, 
      SHARED_CONST_OBJ_t  _parent = nullptr
    );

   ~RvBaseObject();
    RvBaseObject(RvBaseObject const & _other);
    
    RvBaseObject &        operator=(RvBaseObject  const & _other);
    bool                  operator==(RvBaseObject const & _other);

    SHARED_CONST_OBJ_t    Parent() const;
    void                  Parent(SHARED_CONST_OBJ_t _parent);

    uint64_t              UniqueId() const;
    void                  UniqueId(uint64_t _id);

    string                Name() const;
    void                  Name(string _name); 

    optional< VARIANT_t > Property(string _name) const;
    void                  Property(string _name, VARIANT_t _value);

    SHARED_OBJECT_t       ChildObj(string _name) const;
    void                  ChildObj(string _name, bool _register_with_glob_pool = true);

    string                PropsAsIndentedString(uint64_t _level = 0) const;
    string                ChildObjsAsIndentedString(stack<string> & _str_stack, uint64_t _level = 0) const;
    string                ObjectHierarchyAsIndentedString() const;

    string                PropsAsCsvString() const;
    string                ChildObjsAsCsvString(stack<string> & _str_stack, uint64_t _level = 0) const;
    string                ObjectHierarchyAsCsvString() const;

    string                Scope() const;
    void                  Register() const;
    void                  ClearPropertyPool();
    void                  ClearChildObjPool();
    void                  CopyPropertyPool(RvBaseObject  const & _other, bool _merge = false, bool deep_copy = false);
    void                  CopyChildObjPool(RvBaseObject  const & _other, bool _merge = false, bool deep_copy = false);
    void                  CopyExtObjRefPool(RvBaseObject const & _other, bool _merge = false);

    // Static
    static void           ConfigurePropsFromCsv(string _filename);
    static void           ClearGlobalRefPool();
    static void           RegisterWithGlobalRefPool(SHARED_OBJECT_t & _context);
    static void           PrintGlobalRefPool();
};

#endif
