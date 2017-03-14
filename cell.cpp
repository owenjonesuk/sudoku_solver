#include "cell.hpp"
#include <algorithm>


Cell::Cell() : value_(Value::UNSET) {
  setAllValuesPossible();
}

Cell::Cell(const Cell& other) {
  setValue(other.getValue());
}

void Cell::setValue(Value value) {
  if (!poss_[value]) {
    throw "Trying to set cell to impossible value";
  }
  value_ = value;
  if (value == Value::UNSET) {
    setAllPoss(true);
  } else {
    setAllPoss(false);
    poss_[value] = true;
    num_possible_ = 1;
  }
}

std::vector<Cell::Value> Cell::getPossibleValues() {
  std::vector<Cell::Value> possible_values;
  for (Value value : Cell::all_values) {
    if (poss_[value]) {
      possible_values.push_back(value);
    }
  }
  return possible_values;
}

bool Cell::setImpossible(Value value) {
  if (poss_[value]) {
    poss_[value] = false;
    num_possible_--;
    if (num_possible_ == 0) {
      throw "A cell now has no possible values";
    }
  }
  return num_possible_ != 0;
}

void Cell::setAllValuesPossible(){
  for (Value value : Cell::all_values) {
    poss_[value] = true;
  }
  num_possible_ = GRID_SIZE + 1;
}

void Cell::setAllValuesImpossible(){
  for (Value value : Cell::all_values) {
    poss_[value] = false;
  }
  num_possible_ = 0;
}
