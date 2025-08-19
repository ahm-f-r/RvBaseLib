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

variant<bool, string, uint64_t> GetVariant(bool _arg) {
  return variant<bool, string, uint64_t>(_arg);
}

variant<bool, string, uint64_t> GetVariant(string _arg) {
  return variant<bool, string, uint64_t>(_arg);
}

variant<bool, string, uint64_t> GetVariant(uint64_t _arg) {
  return variant<bool, string, uint64_t>(_arg);
}

int main () {

  shared_ptr<RvBaseObject> rv0 = make_shared<RvBaseObject>("Mother", 0);
  rv0->Property("String",                     GetVariant(string("Lachryma")));
  rv0->Property("UInt64",                     GetVariant(43ull));
  rv0->Property("Bool",                       GetVariant(false));

  rv0->ChildObj("Child0", 0);
  rv0->ChildObj("Child0")->Property("String", GetVariant(string("Piecefield")));
  rv0->ChildObj("Child0")->Property("UInt64", GetVariant(77ull));
  rv0->ChildObj("Child0")->Property("Bool",   GetVariant(true));

  rv0->ChildObj("Child1", 1);
  rv0->ChildObj("Child1")->Property("String", GetVariant(string("Satanize")));
  rv0->ChildObj("Child1")->Property("UInt64", GetVariant(97ull));
  rv0->ChildObj("Child1")->Property("Bool",   GetVariant(false));

  shared_ptr<RvBaseObject> rv1 = rv0->ChildObj("Child1");
  rv1->ChildObj("GrandChild0", 0);
  rv1->ChildObj("GrandChild0")->Property("String",  GetVariant(string("Griftwood")));
  rv1->ChildObj("GrandChild0")->Property("UInt64",  GetVariant(32ull));
  rv1->ChildObj("GrandChild0")->Property("Bool",    GetVariant(true));

  cout << rv0->ObjectHierarchyAsIndentedString() << endl;
  
  cout << " --- " << endl;
  string csv_string {rv0->ObjectHierarchyAsCsvString()};
  cout << " --- " << endl;
  cout << csv_string << endl;
  RvBaseScopeUtils::WriteCsvFile("./source/tests/sanity_tests/ObjectHierarchy.csv", csv_string);
  cout << " --- " << endl;
  vector<vector<string> > table {};
  RvBaseScopeUtils::ReadCsvFile("./source/tests/sanity_tests/ObjectHierarchy.csv", table);

  for (auto const & row : table ) {
    string row_elems {};
    for (auto const & cell : row) {
      row_elems += cell;
      row_elems += " ";
    }
    cout << row_elems << endl;
  }

  return 0;
}
