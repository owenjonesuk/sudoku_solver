#include "catch.hpp"
#include "value.hpp"

TEST_CASE ("all_values is the right size and does not contain UNSET", "[value]") {
  REQUIRE(Value::all_values.size() == GRID_SIZE);
}

TEST_CASE ("all_values contains distinct entries", "[value]") {
  for (int i = 0; i < GRID_SIZE; i++) {
    const Value& value_i = Value::all_values[i];
    REQUIRE(!value_i.isUnset());
    for (int j = i + 1; j < GRID_SIZE; j++) {
      const Value& value_j = Value::all_values[j];
      bool value_i_not_equal_to_value_j = 
          (value_i < value_j) || (value_j < value_i);
      REQUIRE(value_i_not_equal_to_value_j);
    }
  }
}

TEST_CASE ("all_values does not contain UNSET", "[value]") {
  for (Value value : Value::all_values) {
    REQUIRE(!value.isUnset());
  }
}

TEST_CASE ("Values are initialised to UNSET by default", "[value]") {
  Value value;
  REQUIRE(value.isUnset());
  std::ostringstream output;
  output << value;
  std::string output_str = output.str();
  REQUIRE(output_str.size() == 1);
  REQUIRE(output_str[0] == Value::UNSET_CHAR);
}

std::vector<Value> get_all_values_with_unset() {
  std::vector<Value> all_values_with_unset(Value::all_values);
  all_values_with_unset.emplace(all_values_with_unset.cbegin(), Value());
  return all_values_with_unset;
}

TEST_CASE ("Values initialised with a character return the same character", "[value]") {
  for (Value value : get_all_values_with_unset()) {
    std::ostringstream output;
    output << value;
    Value new_value(output.str()[0]);
    std::ostringstream new_output;
    new_output << new_value;
    REQUIRE(output.str() == new_output.str());
  }
}

TEST_CASE ("isUnset() works", "[value]") {
  Value value0;
  REQUIRE(value0.isUnset());
  for (Value value : Value::all_values) {
    REQUIRE(!value.isUnset());
  }
}

TEST_CASE ("== operator works", "[value]") {
  std::vector<Value> all_values_with_unset = get_all_values_with_unset();
  for (const Value& value1 : all_values_with_unset) {
    for (const Value& value2 : all_values_with_unset) {
      if (&value1 == &value2) {
        REQUIRE(value1 == value2);
      }
      else {
        REQUIRE(!(value1 == value2));
      }
    }
  }
}

TEST_CASE ("< operator works", "[value]") {
  std::vector<Value> all_values_with_unset = get_all_values_with_unset();
  for (int i = 0; i < all_values_with_unset.size() - 1; i++) {
    REQUIRE(all_values_with_unset[i] < all_values_with_unset[i + 1]);
  }
}
