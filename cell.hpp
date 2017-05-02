#include <array>
#include <exception>
#include <iostream>
#include <map>
#include <vector>
#include "value.hpp"


class Cell {
public:
  const int row;
  const int col;
private:
  Value value_;
  std::map<Value, bool> poss_;
  int num_possible_;
public:
  Cell(int row, int col);
  Value get_value() const { return value_; }
  void set_value(const Value);
  bool is_set() const { return !value_.is_unset(); }
  int get_num_possible() const;
  const std::vector<Value> get_possible_values() const;
  bool set_impossible(const Value);
  
  friend std::ostream& operator<<(std::ostream&, const Cell&);
};

class ModifyingSetCellException : public std::exception {
  const char * what () const throw () {
    return "Cannot modify a cell that is already set";
  }
};

class ImpossibleValueException : public std::exception {
  const char * what () const throw () {
    return "Cannot set cell to an impossible value";
  }
};

class SetImpossibleUnsetException : public std::exception {
  const char * what () const throw () {
    return "Cannot set the value UNSET as impossible";
  }
};
