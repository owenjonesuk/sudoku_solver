#include "catch.hpp"
#include "cell.hpp"

TEST_CASE ("Number of values matches grid size", "[cell]") {
  REQUIRE(Cell::all_values.size() == GRID_SIZE);
  auto find_unset = 
      std::find(Cell::all_values.begin(), Cell::all_values.end(), Value::UNSET);
  REQUIRE(find_unset == Cell::all_values.end());
}

TEST_CASE ("Cells are initialised correctly", "[cell]") {
  Cell cell;
  REQUIRE(cell.getValue() == Value::UNSET);
  REQUIRE(cell.getPossibleValues() == Cell::all_values);
}

TEST_CASE ("Setting the value of a cell to UNSET fails", "[cell]") {
  Cell cell;
  REQUIRE_THROWS(cell.setValue(Value::UNSET));
}

TEST_CASE ("Setting and getting the value of a cell works", "[cell]") {
  for (Value value : Cell::all_values) {
    Cell cell;
    cell.setValue(value);
    REQUIRE(cell.getValue() == value);
  }
}

TEST_CASE ("Cell::isSet() works", "[cell]") {
  for (Value value : Cell::all_values) {
    Cell cell;
    REQUIRE(!cell.isSet());
    cell.setValue(value);
    REQUIRE(cell.isSet());
  }
}

TEST_CASE ("Cell::getNumPossible() fails when cell is already set", "[cell]") {
  for (Value value : Cell::all_values) {
    Cell cell;
    cell.setValue(value);
    REQUIRE_THROWS(cell.getNumPossible());
  }
}

TEST_CASE ("Cell::getNumPossible() works", "[cell]") {
  Cell cell;
  int n = Cell::all_values.size();
  for (Value value : Cell::all_values) {
    REQUIRE(cell.getNumPossible() == n);
    cell.setImpossible(value);
    n--;
  }
  REQUIRE(cell.getNumPossible() == 0);
}

TEST_CASE ("Cell::getPossibleValues() fails when cell is already set", "[cell]") {
  for (Value value : Cell::all_values) {
    Cell cell;
    cell.setValue(value);
    REQUIRE_THROWS(cell.getPossibleValues());
  }
}

TEST_CASE ("Cell::getPossibleValues() works", "[cell]") {
  Cell cell;
  std::vector<Value> values = Cell::all_values;
  REQUIRE(cell.getPossibleValues() == values);
  for (Value value : Cell::all_values) {
    cell.setImpossible(value);
    auto it = std::find(values.begin(), values.end(), value);
    if(it == values.end()) {
      throw "Error looking for a value in values";
    }
    values.erase(it);
    REQUIRE(cell.getPossibleValues() == values);
  }
}

TEST_CASE ("Cell::setImpossible() fails when cell is already set", "[cell]") {
  for (Value value1 : Cell::all_values) {
    for (Value value2 : Cell::all_values) {
      Cell cell;
      cell.setValue(value1);
      REQUIRE_THROWS(cell.setImpossible(value2));
    }
  }
}

TEST_CASE ("Cell::setImpossible() fails with UNSET", "[cell]") {
  Cell cell;
  REQUIRE_THROWS(cell.setImpossible(Value::UNSET));
}

bool isValueInVector(Value value, std::vector<Value> vec) {
  return find(vec.begin(), vec.end(), value) != vec.end();  
}

TEST_CASE ("Cell::setImpossible() works", "[cell]") {
  Cell cell;
  for (Value value : Cell::all_values) {
    REQUIRE(isValueInVector(value, cell.getPossibleValues()));
    cell.setImpossible(value);
    REQUIRE(!isValueInVector(value, cell.getPossibleValues()));
  }
}

TEST_CASE ("Cell::setImpossible() returns correct value", "[cell]") {
  Cell cell;
  bool any_possible;
  int n_possible_values = Cell::all_values.size();
  for (Value value : Cell::all_values) {
    any_possible = cell.setImpossible(value);
    n_possible_values--;
    if (n_possible_values > 0) {
      REQUIRE(any_possible);
    }
    else {
      REQUIRE(!any_possible);
    }
  }
}
