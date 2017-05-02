#include "value.hpp"


const std::vector<Value> Value::all_values = {Value('1'), Value('2'),
    Value('3'), Value('4'), Value('5'), Value('6'), Value('7'), Value('8'),
    Value('9')};

const char Value::UNSET_CHAR = '.';

Value::Value() : x_(UNSET_CHAR) {}

Value::Value(const char input_char) {
  switch (input_char) {
    case '1':
      x_ = '1';
      break;
    case '2':
      x_ = '2';
      break;
    case '3':
      x_ = '3';
      break;
    case '4':
      x_ = '4';
      break;
    case '5':
      x_ = '5';
      break;
    case '6':
      x_ = '6';
      break;
    case '7':
      x_ = '7';
      break;
    case '8':
      x_ = '8';
      break;
    case '9':
      x_ = '9';
      break;
    default:
      x_ = UNSET_CHAR;
      break;
  }
}

bool Value::is_unset() const {
  return x_ == UNSET_CHAR;
}

bool Value::operator ==(const Value& other) const {
  return x_ == other.x_;
}

bool Value::operator <(const Value& other) const {
  return x_ < other.x_;
}

std::ostream& operator<<(std::ostream& out, const Value& value) {
  out << value.x_;
  return out;
}
