#include "cell.hpp"
#include <algorithm>


const std::vector<Value> Cell::all_values = {Value::V1, Value::V2, Value::V3,
    Value::V4, Value::V5, Value::V6, Value::V7, Value::V8, Value::V9};

Cell::Cell() : value_(Value::UNSET) {
  for (Value value : Cell::all_values) {
    poss_[value] = true;
  }
  num_possible_ = all_values.size();
}

// Cell::Cell(const Cell& other) {
//   setValue(other.getValue());
// }

void Cell::setValue(Value new_value) {
  if (isSet()) {
    throw "trying to call setValue() on a cell that's already set";
  }
  else if (new_value == Value::UNSET) {
    throw "cannot set value to UNSET";
  }
  else if (!poss_[new_value]) {
      throw "Trying to set cell to impossible value";
  }
  value_ = new_value;
  for (Value value : Cell::all_values) {
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
  for (Value value : Cell::all_values) {
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
  if (value == Value::UNSET) {
    throw "Can't set UNSET value impossible without setting the value of the cell";
  }
  if (poss_.at(value)) {
    poss_[value] = false;
    num_possible_--;
  }
  return num_possible_ != 0;
}
