#ifndef RV_BASE_UTILS_H
#define RV_BASE_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <regex>
#include <vector>

#include "RvBaseEnums.h"

using namespace std;

namespace RvBaseAddrUtils {

  template<typename T> uint64_t Mask(T _size) {
    return ~((1ull << _size)-1);
  }

  TEMPLATE_t uint64_t Offset(T _size) {
    return ((1ull << _size)-1);
  }

  TEMPLATE_t uint64_t Next(T _size, uint64_t _addr) {
    return ((Mask<T>(_size) & _addr) + (1ull << _size));
  }

  TEMPLATE_t bool IsCrossing(T _size, uint64_t _addr, uint64_t _increment) {
    return ((_addr + _increment) & Mask<T>(_size)) == Next<T>(_size, _addr);
  }

  TEMPLATE_t bool IsPresent(T _size, uint64_t _addr) {
    return (_addr & Mask<T>(_size)) == Mask(_size);
  }
}

namespace RvBaseDataUtils {

}

namespace RvBaseScopeUtils {

  // ==========================================================================
  static inline queue<string> SplitScope(string _scope, string _delim = ".")
  // ==========================================================================
  {
    size_t        pos_start {0};
    size_t        pos_end   {0};
    size_t        delim_len {_delim.length()};
    string        token     {};
    queue<string> result    {};
    do {
      pos_end   = _scope.find(_delim, pos_start);
      token     = _scope.substr(pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      result.push(token);
    } while (pos_end != string::npos);
    return result;
  }

  // ==========================================================================
  static inline bool MatchScope(queue<string> & _pattern, queue<string> & _object)
  // ==========================================================================
  {
    string pattern {};
    string object  {};
    
    do {
      pattern += _pattern.front();
      _pattern.pop();
      if (not _pattern.empty()) {
        pattern += "__";
      }
    } while (not _pattern.empty());

    do {
      object += _object.front();
      _object.pop();
      if (not _object.empty()) {
        object += "__";
      }
    } while (not _object.empty());

    regex star_replace("\\*");
    regex qmrk_replace("\\?");
    auto wildcard_pattern = 
      regex_replace( regex_replace(pattern, star_replace, ".*"), qmrk_replace, "." );    
    regex wildcard_regex("^" + wildcard_pattern + "$");
    bool result = regex_match(object, wildcard_regex);
    cout << "ObjectScope  : " << object << endl;
    cout << "RegExPattern : " << wildcard_pattern << endl; 
    cout << "Match        : " << boolalpha << result << endl;
    return result;
  }

  // ==========================================================================
  static inline void ReadCsvFile(string const & _filename, vector<vector<string> > & _table)
  // ==========================================================================
  {
    ifstream file(_filename);
    if (!file.is_open()) {
        cerr << "(ERROR) RvBaseScopeUtils::ReadCsvFile() Failed to open file: " << _filename << endl;
        assert(false);
    }
    string line;
    while (getline(file, line)) {
      vector<string> row;
      stringstream ss(line);
      string cell;
      while (getline(ss, cell, ',')) {
        row.push_back(cell);
      }
      _table.push_back(row);
    }
    file.close();
  }

  // ==========================================================================
  static inline void WriteCsvFile(string const & _filename, string const & _csv_string)
  // ==========================================================================
  {
    ofstream file(_filename);
    if (!file.is_open()) {
      cerr << "(ERROR) RvBaseScopeUtils::WriteCsvFile() Failed to open file: " << _filename << endl;
      assert(false);
    }
    file << _csv_string;
    file.flush();
    file.close();
  }
}

#endif
