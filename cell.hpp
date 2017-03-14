#include <array>
#include <iostream>
#include <map>
#include <vector>

#define GRID_SIZE 9

class Cell {
public:
  enum Value {
    UNSET = 0,
    V1 = 1,
    V2 = 2,
    V3 = 3,
    V4 = 4,
    V5 = 5,
    V6 = 6,
    V7 = 7,
    V8 = 8,
    V9 = 9 // must be GRID_SIZE
  };
  Value all_values[GRID_SIZE + 1] = {Value::UNSET, Value::V1, Value::V2,
     Value::V3,  Value::V4, Value::V5, Value::V6, Value::V7, Value::V8,
      Value::V9};
private:
  Value value_;
  std::map<Value, bool> poss_;
  int num_possible_;
public:
  Cell();
  Cell(const Cell&);
  Value getValue() const { return value_; }
  void setValue(Value);
  bool isSet() { return value_ != Value::UNSET; }
  int getNumPossible() { return num_possible_; }
  std::vector<Cell::Value> getPossibleValues();
  bool setImpossible(Value);
private:
  void setAllValuesPossible();
  void setAllValuesImpossible();
  void checkValid();
};