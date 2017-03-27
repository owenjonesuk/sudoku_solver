#include <array>
#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include "value.hpp"


class Cell {
private:
  Value value_;
  std::map<Value, bool> poss_;
  int num_possible_;
public:
  Cell();
  const Value& getValue() const { return value_; }
  void setValue(Value);
  bool isSet() const { return !value_.isUnset(); }
  int getNumPossible() const;
  const std::vector<Value> getPossibleValues() const;
  bool setImpossible(Value);
  friend std::ostream& operator<<(std::ostream&, const Cell&);
};

class ModifyingSetCellException : public std::exception {
  const char * what () const throw () {
    return "Cannot modify a cell that is already set";
  }
}

class ImpossibleValueException : public std::exception {
  const char * what () const throw () {
    return "Cannot set cell to an impossible value";
  }
}

class SetImpossibleUnsetException : public std::exception {
  const char * what () const throw () {
    return "Cannot set the value UNSET as impossible";
  }
}