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

#include "RvBaseObject.h"

using namespace std;

int main () {

  RvBaseProperty<uint64_t> const * prop0 = new RvBaseProperty<uint64_t>("uint64_t", 99);
  prop0->Print();


  RvBaseProperty<bool> const * prop1 = new RvBaseProperty<bool>("bool", true);
  prop1->Print();

  RvBaseProperty<string> const * prop2 = new RvBaseProperty<string>("string", "hello");
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
  
  cout << "Scope: " << rv0->Scope() << endl;
  cout << "Scope: " << rv1->Scope() << endl;
  cout << "Scope: " << rv2->Scope() << endl;
  cout << "Scope: " << rv3->Scope() << endl;

  // variant<bool, uint64_t, string> value = to_string("value");
  // rv0->Property(to_string("key"), value);

  return 0;
}
