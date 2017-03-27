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
    throw ModifyingSetCellException;
  }
  if (new_value.isUnset()) {
    // nothing to do
    return;
  }
  if (!poss_[new_value]) {
    throw ImpossibleValueException;
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
    throw ModifyingSetCellException;
  }
  return num_possible_;
}

const std::vector<Value> Cell::getPossibleValues() const {
  if (isSet()) {
    throw ModifyingSetCellException;
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
    throw ModifyingSetCellException;
  }
  if (value.isUnset()) {
    throw SetImpossibleUnsetException;
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
