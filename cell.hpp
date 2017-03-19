#include <array>
#include <iostream>
#include <map>
#include <vector>
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
