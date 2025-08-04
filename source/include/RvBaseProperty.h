#ifndef RV_BASE_PROPERTY_H
#define RV_BASE_PROPERTY_H

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>

#include "RvBaseUtils.h"
#include "RvBaseEnums.h"

using namespace std;

template <typename T> class RvBaseProperty
{
  private :
    string                          mName {"Undefined"};    
    T                               mValue;
    bool                            mValid {false};
    static uint64_t                 mRefCount;

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
template < typename T > uint64_t RvBaseProperty<T>::mRefCount = 0;


class RvBaseBoolProperty : public RvBaseProperty<bool> 
{
  public:
    explicit RvBaseBoolProperty(string _name, bool _value);
};


class RvBaseUInt64Property : public RvBaseProperty<uint64_t>
{
  public:
    explicit RvBaseUInt64Property(string _name, uint64_t _value);
};


class RvBaseStringProperty : public RvBaseProperty<string>
{
  public: 
    explicit RvBaseStringProperty(string _name, string _value);
};

#endif