#include <iostream>
#include <vector>

#define GRID_SIZE 9


class Value {
public:
  static const std::vector<Value> all_values;
  static const char UNSET_CHAR;
private:
  char x_;
public:
  Value();
  Value(const char input_char);
  bool is_unset() const;
  bool operator ==(const Value&) const;
  bool operator <(const Value&) const;
  
  friend std::ostream& operator<<(std::ostream&, const Value&);
};
