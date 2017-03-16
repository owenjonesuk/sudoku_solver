#include <array>
#include <iostream>
#include <map>
#include <vector>

#define GRID_SIZE 9

enum class Value {
  UNSET = 0, // this is not included in Cell::all_values
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

class Cell {
public:
  static const std::vector<Value> all_values;
private:
  Value value_;
  std::map<Value, bool> poss_;
  int num_possible_;
public:
  Cell();
  // Cell(const Cell&);
  const Value& getValue() const { return value_; }
  void setValue(Value);
  bool isSet() const { return value_ != Value::UNSET; }
  int getNumPossible() const;
  const std::vector<Value> getPossibleValues() const;
  bool setImpossible(Value);
};