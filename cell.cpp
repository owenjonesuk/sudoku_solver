#include <algorithm>
#include "cell.hpp"
#include <utility>

Cell::Cell(int row, int col) : value_(Value()), row(row), col(col) {
  for (Value value : Value::all_values) {
    poss_[value] = true;
  }
  num_possible_ = Value::all_values.size();
}

void Cell::set_value(const Value new_value) {
  if (is_set()) {
    throw ModifyingSetCellException();
  }
  if (new_value.is_unset()) {
    // nothing to do
    return;
  }
  if (!poss_[new_value]) {
    throw ImpossibleValueException();
  }
  value_ = new_value;
  // We don't strictly need to keep poss_ and num_possible_ updated, because
  // they can't be accessed once the cell is set, but we do it anyway
  for (Value value : Value::all_values) {
    poss_[value] = false;
  }
  poss_[new_value] = true;
  num_possible_ = 1;
}

int Cell::get_num_possible() const {
  if (is_set()) {
    throw ModifyingSetCellException();
  }
  return num_possible_;
}

const std::vector<Value> Cell::get_possible_values() const {
  if (is_set()) {
    throw ModifyingSetCellException();
  }
  std::vector<Value> possible_values;
  for (Value value : Value::all_values) {
    if (poss_.at(value)) {
      possible_values.push_back(value);
    }
  }
  return possible_values;
}

bool Cell::set_impossible(const Value value) {
  if (is_set()) {
    throw ModifyingSetCellException();
  }
  if (value.is_unset()) {
    throw SetImpossibleUnsetException();
  }
  if (poss_.at(value)) {
    poss_[value] = false;
    --num_possible_;
  }
  // return true if the cell still has any possible values
  return num_possible_ != 0;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.get_value();
  return os;
}
