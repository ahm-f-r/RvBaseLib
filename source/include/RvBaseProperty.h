#ifndef RV_BASE_PROPERTY_H
#define RV_BASE_PROPERTY_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>

#include "RvBaseCommon.d"

using namespace std;

TEMPLATE_t class RvBaseProperty
{
  private :
    string            mName {"Undefined"};    
    T                 mValue;
    bool              mValid {false};
    static uint64_t   mRefCount;

  public :
    explicit RvBaseProperty(string _name, T _value);
    ~RvBaseProperty();
    RvBaseProperty(RvBaseProperty const & _other);
    RvBaseProperty & operator=(RvBaseProperty const & _other);
    bool operator==(RvBaseProperty const & _other);
    
    string  Name() const;
    void    Name(string _name);

    void    Value(T _value); 
    T       Value() const;

    // Helper Function
    uint64_t  RefCount() const;
    string    AsString() const;
    void      ClearValid();
    void      SetValid();
    bool      IsValid() const;
};

#endif