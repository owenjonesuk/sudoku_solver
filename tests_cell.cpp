#include "catch.hpp"
#include "cell.hpp"


std::vector<Value> get_all_values_with_unset() {
  std::vector<Value> all_values_with_unset(Value::all_values);
  all_values_with_unset.emplace(all_values_with_unset.cbegin(), Value());
  return all_values_with_unset;
}

bool isValueInVector(Value value, std::vector<Value> vec) {
  return find(vec.begin(), vec.end(), value) != vec.end();  
}

TEST_CASE ("Cells are created correctly", "[cell]") {
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      Cell cell(row, col);
      REQUIRE(cell.row == row);
      REQUIRE(cell.col == col);
    }
  }

  Cell cell(0,0);
  REQUIRE(cell.get_value() == Value());
  REQUIRE(cell.get_num_possible() == Value::all_values.size());
  REQUIRE(cell.get_possible_values() == Value::all_values);
}

TEST_CASE ("Cannot set value of cell that is already set", "[cell]") {
  Cell cell(0, 0);
  cell.set_value('1');
  for (Value value : get_all_values_with_unset()) {
    REQUIRE_THROWS_AS(cell.set_value(value), ModifyingSetCellException);
  }
}

TEST_CASE ("Setting the value of a cell to UNSET does nothing", "[cell]") {
  Cell cell1(0, 0);
  Cell cell2(0, 0);
  Value unset_value;
  cell1.set_value(unset_value);
  REQUIRE(cell1.get_value() == cell2.get_value());
  REQUIRE(cell1.get_num_possible() == cell2.get_num_possible());
  REQUIRE(cell1.get_possible_values() == cell2.get_possible_values());
}

TEST_CASE ("Cannot set value of cell to an impossible value", "[cell]") {
  Value value('1');
  Cell cell(0, 0);
  cell.set_impossible(value);
  REQUIRE_THROWS_AS(cell.set_value(value), ImpossibleValueException);
}

TEST_CASE ("Set and get the value of a cell", "[cell]") {
  for (Value value : Value::all_values) {
    Cell cell(0, 0);
    cell.set_value(value);
    REQUIRE(cell.get_value() == value);
  }
}

TEST_CASE ("Can tell if a cell is set", "[cell]") {
  Cell unset_cell(0, 0);
  REQUIRE(!unset_cell.is_set());
  for (Value value : Value::all_values) {
    Cell cell(0, 0);
    cell.set_value(value);
    REQUIRE(cell.is_set());
  }
}

TEST_CASE ("Cannot get number of possible values of a set cell", "[cell]") {
  Cell cell(0, 0);
  cell.set_value('3');
  REQUIRE_THROWS_AS(cell.get_num_possible(), ModifyingSetCellException);
}

TEST_CASE ("Get number of possible values", "[cell]") {
  Cell cell(0, 0);
  int n = Value::all_values.size();
  for (Value value : Value::all_values) {
    REQUIRE(cell.get_num_possible() == n);
    cell.set_impossible(value);
    --n;
  }
  REQUIRE(cell.get_num_possible() == 0);
}

TEST_CASE ("Cannot get possible values of a set cell", "[cell]") {
  Cell cell(0, 0);
  cell.set_value('5');
  REQUIRE_THROWS_AS(cell.get_possible_values(), ModifyingSetCellException);
}

TEST_CASE ("Get possible values", "[cell]") {
  Cell cell(0, 0);
  std::vector<Value> values = Value::all_values;
  REQUIRE(cell.get_possible_values() == values);
  for (Value value : Value::all_values) {
    cell.set_impossible(value);
    auto it = std::find(values.begin(), values.end(), value);
    REQUIRE(it != values.end());
    values.erase(it);
    REQUIRE(cell.get_possible_values() == values);
  }
}

TEST_CASE ("Cannot set a value as impossible for a set cell", "[cell]") {
  Cell cell(0, 0);
  cell.set_value(Value::all_values[0]);
  REQUIRE_THROWS_AS(cell.set_impossible(Value::all_values[1]),
                    ModifyingSetCellException);
}

TEST_CASE ("Cannot set UNSET value as impossible", "[cell]") {
  Cell cell(0, 0);
  Value unset_value;
  REQUIRE_THROWS_AS(cell.set_impossible(unset_value),
                    SetImpossibleUnsetException);
}

TEST_CASE ("Set a value as impossible", "[cell]") {
  Cell cell(0, 0);
  for (Value value : Value::all_values) {
    REQUIRE(isValueInVector(value, cell.get_possible_values()));
    cell.set_impossible(value);
    REQUIRE(!isValueInVector(value, cell.get_possible_values()));
  }
}

TEST_CASE ("Setting a value as impossible returns whether there are any possible values left",
           "[cell]") {
  Cell cell(0, 0);
  bool any_possible;
  int n_possible_values = Value::all_values.size();
  for (Value value : Value::all_values) {
    any_possible = cell.set_impossible(value);
    --n_possible_values;
    if (n_possible_values > 0) {
      REQUIRE(any_possible);
    }
    else {
      REQUIRE(!any_possible);
    }
  }
}

TEST_CASE ("Print a cell", "[cell]") {
  for (Value value : Value::all_values) {
    std::ostringstream expected_output;
    expected_output << value;
    Cell cell(0, 0);
    cell.set_value(value);
    std::ostringstream output;
    output << cell;
    std::string output_str = output.str();
    REQUIRE(output_str.size() == 1);
    REQUIRE(output_str[0] == expected_output.str()[0]);
  }
}
