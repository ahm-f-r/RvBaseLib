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

  shared_ptr<RvBaseObject> rv0 = make_shared<RvBaseObject>("Mother", 0);
  shared_ptr<RvBaseObject> rv1 = make_shared<RvBaseObject>("Child",  1);
  shared_ptr<RvBaseObject> rv2 = make_shared<RvBaseObject>("Child",  2);
  shared_ptr<RvBaseObject> rv3 = make_shared<RvBaseObject>("Child",  3);

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

  variant<bool, string, uint64_t> val0 = "value";
  variant<bool, string, uint64_t> val1 = 55ull;
  variant<bool, string, uint64_t> val2 = false;

  rv1->Property("string",   val0);  
  rv2->Property("uint64_t", val1);
  rv3->Property("bool",     val2);

  rv0->ChildObj(rv1->Name(), rv1->Id());
  rv0->ChildObj(rv2->Name(), rv2->Id());
  rv0->ChildObj(rv3->Name(), rv3->Id());

  variant<bool, string, uint64_t> val00 = "key";
  variant<bool, string, uint64_t> val11 = 77ull;
  variant<bool, string, uint64_t> val22 = true;

  rv0->Property("string",   val00);  
  rv0->Property("uint64_t", val11);
  rv0->Property("bool",     val22);

  shared_ptr<RvBaseObject> rv4 = make_shared<RvBaseObject>("Father", 4);

  rv4->CopyChildObjPool(*rv0, true, true);
  cout << "CopyChild" << endl;

  rv4->CopyPropertyPool(*rv0, true, true);
  cout << "CopyProp" << endl;

  cout  << "string = " 
        << (
          rv4->Property("string").has_value() ? 
            get<string>(rv4->Property("string").value()) : 
            static_cast<string>(0)
          )
        << endl; 
  cout  << "uint64_t = " 
        << (
          rv4->Property("uint64_t").has_value() ? 
            get<uint64_t>(rv4->Property("uint64_t").value()) : 
            static_cast<uint64_t>(0)
          )
        << endl; 
  cout  << "bool = "
        << (
          rv4->Property("bool").has_value() ? 
            get<bool>(rv4->Property("bool").value()) : 
            static_cast<bool>(0)
          )
        << endl; 

  return 0;
}
