#include "cell.hpp"
#include <algorithm>


Cell::Cell() : value_(Value()) {
  for (Value value : Value::all_values) {
    poss_[value] = true;
  }
  num_possible_ = Value::all_values.size();
}

void Cell::setValue(Value new_value) {
  if (isSet()) {
    throw "trying to call setValue() on a cell that's already set";
  }
  if (new_value.isUnset()) {
    // nothing to do
    return;
  }
  if (!poss_[new_value]) {
    throw "Trying to set cell to impossible value";
  }
  value_ = new_value;
  for (Value value : Value::all_values) {
    poss_[value] = false;
  }
  poss_[new_value] = true;
  num_possible_ = 1;
}

int Cell::getNumPossible() const {
  if (isSet()) {
    throw "trying to call getNumPossible() on a cell that's already set";
  }
  return num_possible_;
}

const std::vector<Value> Cell::getPossibleValues() const {
  if (isSet()) {
    throw "trying to call getPossibleValues() on a cell that's already set";
  }
  std::vector<Value> possible_values;
  for (Value value : Value::all_values) {
    if (poss_.at(value)) {
      possible_values.push_back(value);
    }
  }
  return possible_values;
}

bool Cell::setImpossible(Value value) {
  if (isSet()) {
    throw "trying to call setImpossible() on a cell that's already set";
  }
  if (value.isUnset()) {
    throw "Can't set UNSET value impossible without setting the value of the cell";
  }
  if (poss_.at(value)) {
    poss_[value] = false;
    num_possible_--;
  }
  return num_possible_ != 0;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.getValue();
  return os;
}
