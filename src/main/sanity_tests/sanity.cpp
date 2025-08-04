#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <map>
#include <memory>

#include "RvBaseUtils.h"
#include "RvBaseEnums.h"
#include "RvBaseProperty.h"
#include "RvBaseObject.h"

using namespace std;

int main () {

  RvBaseUInt64Property const * prop0 = new RvBaseUInt64Property("uint64_t", 99);
  prop0->Print();

  RvBaseBoolProperty const * prop1 = new RvBaseBoolProperty("bool", true);
  prop1->Print();

  RvBaseStringProperty const * prop2 = new RvBaseStringProperty("string", "hello");
  prop2->Print();

  shared_ptr<RvBaseObject> rv0 = make_shared<RvBaseObject>("Parent", 0);
  shared_ptr<RvBaseObject> rv1 = make_shared<RvBaseObject>("Child",  1, rv0);
  shared_ptr<RvBaseObject> rv2 = make_shared<RvBaseObject>("GrandChild", 2, rv1);
  shared_ptr<RvBaseObject> rv3 = make_shared<RvBaseObject>("GrandChild", 3, rv1);

  cout << "Name: " << rv0->Name() << endl;
  cout << "Name: " << rv1->Name() << endl;
  cout << "Name: " << rv2->Name() << endl;
  cout << "Name: " << rv3->Name() << endl;

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

  return 0;
}
