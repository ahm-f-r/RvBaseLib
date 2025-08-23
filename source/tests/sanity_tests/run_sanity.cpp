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
  shared_ptr<RvBaseObject> rv0 = make_shared<RvBaseObject>("Father", 0);
  RvBaseObject::RegisterWithRefPool(rv0);
  rv0->Property("Name",     GetVariant(string("Tobias")));
  rv0->Property("Age",      GetVariant(77ull));
  rv0->Property("Employed", GetVariant(false));

  rv0->ChildObj("Child0", 0);
  shared_ptr<RvBaseObject> rv00 = rv0->ChildObj("Child0");
  RvBaseObject::RegisterWithRefPool(rv00);
  rv00->Property("Name",     GetVariant(string("Sylvain")));
  rv00->Property("Age",      GetVariant(30ull));
  rv00->Property("Employed", GetVariant(true));

  rv0->ChildObj("Child1", 0); 
  shared_ptr<RvBaseObject> rv01 = rv0->ChildObj("Child1");
  RvBaseObject::RegisterWithRefPool(rv01);
  rv01->Property("Name",     GetVariant(string("Per")));
  rv01->Property("Age",      GetVariant(31ull));
  rv01->Property("Employed", GetVariant(false));

  rv01->ChildObj("GrandChild0", 0);
  shared_ptr<RvBaseObject> rv010 = rv01->ChildObj("GrandChild0");
  RvBaseObject::RegisterWithRefPool(rv010);
  rv010->Property("Name",      GetVariant(string("Rain")));
  rv010->Property("Age",       GetVariant(10ull));
  rv010->Property("Employed",  GetVariant(false));

  cout << " ======================================================================== " << endl;
  cout << "  * Set Hierarchical Objects with rv0 as root node.                       " << endl;
  cout << "  * Print Hierarchical Objects.                                           " << endl;
  cout << " ======================================================================== " << endl;
  cout << rv0->ObjectHierarchyAsIndentedString() << endl;
  
  cout << " ======================================================================== " << endl;
  cout << "  * Save Object Hierarchy as CSV string.                                  " << endl;
  cout << "  * Print and save string to CSV file.                                    " << endl;
  cout << " ======================================================================== " << endl;
  string csv_string {rv0->ObjectHierarchyAsCsvString()};
  cout << csv_string << endl;
  RvBaseScopeUtils::WriteCsvFile("./source/tests/sanity_tests/GoldenRef.csv", csv_string);

  cout << " ======================================================================== " << endl;
  cout << "  * Read Object Hierarchy from CSV file into a vector table.              " << endl;
  cout << "  * Print table.                                                          " << endl;
  cout << " ======================================================================== " << endl;  
  vector<vector<string> > table {};
  RvBaseScopeUtils::ReadCsvFile("./source/tests/sanity_tests/GoldenRef.csv", table);

  for (auto const & row : table ) {
    string row_elems {};
    for (auto const & cell : row) {
      row_elems += cell;
      row_elems += ",";
    }
    // Remove the trailing comma
    row_elems = row_elems.substr(0, row_elems.length() - 1);
    cout << row_elems << endl;
  }
  cout << " ======================================================================== " << endl;
  cout << "  * Print RefPool.                                                        " << endl;
  cout << " ======================================================================== " << endl;  
  RvBaseObject::PrintRefPool();

  cout << " ======================================================================== " << endl;
  cout << "  * Configure Object Props via Configurator.                              " << endl;
  cout << "  * Print Hierarchical Objects.                                           " << endl;
  cout << " ======================================================================== " << endl;  
  RvBaseObject::ConfigurePropsFromCsv("./source/tests/sanity_tests/Pattern.csv");
  cout << rv0->ObjectHierarchyAsIndentedString() << endl;

  return 0;
}
