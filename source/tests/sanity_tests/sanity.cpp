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

// #include "RvBaseUtils.h"
// #include "RvBaseEnums.h"
// #include "RvBaseProperty.h"
#include "RvBaseObject.h"

using namespace std;

// using sConstObj_t = shared_ptr<const RvBaseObject>;
// using sObj_t      = shared_ptr<RvBaseObject>;
// using vProp_t     = variant<shared_ptr<RvBaseBoolProperty>,
//                             shared_ptr<RvBaseStringProperty>,
//                             shared_ptr<RvBaseUInt64Property> >;
// using sBoolProp_t = shared_ptr<RvBaseBoolProperty>;
// using sStrProp_t  = shared_ptr<RvBaseStringProperty>;
// using sUIntProp_t = shared_ptr<RvBaseUInt64Property>;
// using vValue_t    = variant<bool, uint64_t, string>;

int main () {
/*
  RvBaseUInt64Property const * prop0 = new RvBaseUInt64Property("uint64_t", 99);
  prop0->Print();

  RvBaseBoolProperty const * prop1 = new RvBaseBoolProperty("bool", true);
  prop1->Print();

  RvBaseStringProperty const * prop2 = new RvBaseStringProperty("string", "hello");
  prop2->Print();
*/
  shared_ptr<RvBaseObject> rv0 = make_shared<RvBaseObject>("Parent", 0);
  shared_ptr<RvBaseObject> rv1 = make_shared<RvBaseObject>("Child",  1, rv0);
  shared_ptr<RvBaseObject> rv2 = make_shared<RvBaseObject>("GrandChild", 2, rv1);
  shared_ptr<RvBaseObject> rv3 = make_shared<RvBaseObject>("GrandChild", 3, rv1);

  cout << "Name: " << rv0->Name() << endl;
  cout << "Name: " << rv1->Name() << endl;
  cout << "Name: " << rv2->Name() << endl;
  cout << "Name: " << rv3->Name() << endl;

/*
  cout << "Id: " << rv0->Id() << endl;
  cout << "Id: " << rv1->Id() << endl;
  cout << "Id: " << rv2->Id() << endl;
  cout << "Id: " << rv3->Id() << endl;
  
  variant<bool, uint64_t, string> value = "value";
  rv0->Property("key", value);

  cout << "Scope: " << rv0->Scope() << endl;
  cout << "Scope: " << rv1->Scope() << endl;
  cout << "Scope: " << rv2->Scope() << endl;
  cout << "Scope: " << rv3->Scope() << endl;
*/
  return 0;
}
