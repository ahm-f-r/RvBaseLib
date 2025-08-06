#ifndef RV_BASE_PROPERTY_H
#define RV_BASE_PROPERTY_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>

using namespace std;

template <typename T> class RvBaseProperty
{
  private :
    string            mName {"Undefined"};    
    T                 mValue;
    bool              mValid {false};
    static uint64_t   mBasePropertyRefCount;

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
    void    Print() const;
    void    ClearValid();
    void    SetValid();
    bool    IsValid() const;
};

#endif