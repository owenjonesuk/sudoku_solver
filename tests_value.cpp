#include "catch.hpp"
#include "value.hpp"


bool value_is_unset(Value value) {
  return value.is_unset();
}

std::string get_string_from_value(Value value) {
  std::ostringstream output;
  output << value;
  return output.str();
}

std::vector<Value> get_all_values_with_unset() {
  std::vector<Value> all_values_with_unset(Value::all_values);
  all_values_with_unset.emplace(all_values_with_unset.cbegin(), Value());
  return all_values_with_unset;
}

TEST_CASE ("List of all values is the right size", "[value]") {
  REQUIRE(Value::all_values.size() == GRID_SIZE);
}

TEST_CASE ("List of all values does not contain UNSET", "[value]") {
  auto iter = std::find_if(Value::all_values.begin(),
                           Value::all_values.end(),
                           value_is_unset);
  REQUIRE(iter == Value::all_values.end());
}

TEST_CASE ("List of all values contains distinct entries", "[value]") {
  for (int i = 0; i < GRID_SIZE; ++i) {
    const Value& value_i = Value::all_values[i];
    for (int j = i + 1; j < GRID_SIZE; ++j) {
      const Value& value_j = Value::all_values[j];
      // Assign this expression to a boolean because Catch can't cope with it
      // directly
      bool value_i_not_equal_to_value_j = 
          (value_i < value_j) || (value_j < value_i);
      REQUIRE(value_i_not_equal_to_value_j);
    }
  }
}

TEST_CASE ("Printing list of all values gives distinct strings", "[value]") {
  std::set<std::string> all_values_strings;
  for (int i = 0; i < GRID_SIZE; ++i) {
    all_values_strings.emplace(get_string_from_value(Value::all_values[i]));
  }
  REQUIRE(all_values_strings.size() == Value::all_values.size());
}

TEST_CASE ("Values are UNSET by default", "[value]") {
  Value value;
  REQUIRE(value.is_unset());
  std::string value_str = get_string_from_value(value);
  REQUIRE(value_str.size() == 1);
  REQUIRE(value_str[0] == Value::UNSET_CHAR);
}

TEST_CASE ("Values from a known char print as the same char", "[value]") {
  for (Value value : get_all_values_with_unset()) {
    std::string value_str = get_string_from_value(value);
    Value new_value(value_str[0]);
    std::string new_value_str = get_string_from_value(new_value);
    REQUIRE(value_str == new_value_str);
  }
}

TEST_CASE ("Values from an unknown char are UNSET", "[value]") {
  char unknown_chars[] = {'0', '!', '-', ' '};
  for (const char c : unknown_chars) {
    Value value(c);
    REQUIRE(value.is_unset());
    std::string value_str = get_string_from_value(value);
    REQUIRE(value_str.size() == 1);
    REQUIRE(value_str[0] == Value::UNSET_CHAR);
  }
}

TEST_CASE ("Can tell if a value is unset", "[value]") {
  Value value0;
  REQUIRE(value0.is_unset());
  Value value1(Value::UNSET_CHAR);
  REQUIRE(value1.is_unset());
  for (Value value : Value::all_values) {
    REQUIRE(!value.is_unset());
  }
}

TEST_CASE ("Compare values for equality", "[value]") {
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

TEST_CASE ("Compare values for ordering", "[value]") {
  std::vector<Value> all_values_with_unset = get_all_values_with_unset();
  for (int i = 0; i < all_values_with_unset.size() - 1; ++i) {
    REQUIRE(all_values_with_unset[i] < all_values_with_unset[i + 1]);
  }
}
