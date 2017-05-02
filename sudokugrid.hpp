#include <stack>
#include <string>
#include "cell.hpp"


class SudokuGrid {
private:
  std::vector<Cell> cells_;
  bool all_cells_have_possible_values_;
public:
  SudokuGrid();
  SudokuGrid(const SudokuGrid&);
  SudokuGrid(std::string);
  void set_cell_value(int, int, Value);
  void set_cells_with_one_possible_value();
  bool is_completed() const;
  bool all_cells_have_possible_values() const;
  const Cell& get_cell_to_condition_on() const;
private:
  void validate_cell_indices(int row, int col) const;
  Cell& get_cell(int row, int col);
  const Cell& get_cell_const(int row, int col) const;
  Value get_value(int row, int col) const;
  const std::array<Cell*, GRID_SIZE> get_row(const Cell& cell);
  const std::array<Cell*, GRID_SIZE> get_column(const Cell& cell);
  const std::array<Cell*, GRID_SIZE> get_box(const Cell& cell);
  
  friend std::ostream& operator<<(std::ostream&, const SudokuGrid&);
};

class FailedToOpenFileException : public std::exception {
public:
  FailedToOpenFileException(std::string file_location)
    : file_location(file_location)
    { }
  
private:
  const std::string file_location;

  const char * what () const throw () {
    std::string message = "Failed to open file " + file_location;
    return message.c_str();
  }
};

class NoUnsetCellsException : public std::exception {
  const char * what () const throw () {
    return "There are no unset cells to condition on";
  }
};

class CellIndicesOutOfRangeException : public std::exception {
  const char * what () const throw () {
    return "Cell indices out of range";
  }
};