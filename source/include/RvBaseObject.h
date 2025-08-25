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
    shared_ptr<const RvBaseObject>  sParent {};
    uint64_t                        mId     {};
    string                          mName   {};

    map<string, SHARED_VARIANT_t>           mPropertyPool {};
    map<string, shared_ptr<RvBaseObject> >  mChildObjPool  {};

    static uint64_t mRefCount;
    static vector<shared_ptr<RvBaseObject> > mObjRefPool;

  public :
    explicit RvBaseObject(
      string                          _name, 
      uint64_t                        _id,
      shared_ptr<const RvBaseObject> _parent = nullptr);
   ~RvBaseObject();
    RvBaseObject(RvBaseObject const & _other);
    RvBaseObject & operator=(RvBaseObject const & _other);
    bool operator==(RvBaseObject const & _other);

    shared_ptr<const RvBaseObject> Parent() const;
    void Parent(shared_ptr<const RvBaseObject> _parent);

    uint64_t  Id() const;
    void      Id(uint64_t _id);

    string    Name() const;
    void      Name(string _name); 

    optional< VARIANT_t > Property(string _name) const;
    void Property(string _name, VARIANT_t _value);

    shared_ptr<RvBaseObject> ChildObj(string _name) const;
    void ChildObj(string _name, uint64_t _id);

    string  PropsAsIndentedString(uint64_t _level = 0) const;
    string  ChildObjsAsIndentedString(stack<string> & _str_stack, uint64_t _level = 0) const;
    string  ObjectHierarchyAsIndentedString() const;

    string  PropsAsCsvString() const;
    string  ChildObjsAsCsvString(stack<string> & _str_stack, uint64_t _level = 0) const;
    string  ObjectHierarchyAsCsvString() const;

    string  Scope() const;
    void    ClearPropertyPool();
    void    ClearChildObjPool();
    void    CopyPropertyPool(RvBaseObject const & _other, bool _merge = false, bool deep_copy = false);
    void    CopyChildObjPool(RvBaseObject const & _other, bool _merge = false, bool deep_copy = false);

    static void ConfigurePropsFromCsv(string _filename);
    static void ClearRefPool();
    static void RegisterWithRefPool(shared_ptr<RvBaseObject> & _context);
    static void PrintRefPool();
};

#endif
