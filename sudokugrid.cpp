#include <assert.h>
#include <climits>
#include <fstream>
#include "sudokugrid.hpp"


SudokuGrid::SudokuGrid() {
  cells_.reserve(GRID_SIZE * GRID_SIZE);
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      cells_.emplace_back(Cell(row, col));
    }
  }
  all_cells_have_possible_values_ = true;
}

SudokuGrid::SudokuGrid(const SudokuGrid& other) : SudokuGrid() {
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      Value value = other.get_cell_const(row, col).get_value();
      set_cell_value(row, col, value);
    }
  }
}

SudokuGrid::SudokuGrid(std::string file_location) : SudokuGrid() {
  std::ifstream file(file_location);
  if (!file.is_open()) {
    throw(FailedToOpenFileException(file_location));
  } else {
    std::string line;
    for (int row = 0; row < GRID_SIZE; ++row) {
      getline(file, line);
      for (int col = 0; col < GRID_SIZE; ++col) {
        if (col <= line.length()) {
          set_cell_value(row, col, Value(line[col]));
        }
      }
    }
  }
}

void SudokuGrid::set_cell_value(const int row,
                                const int col,
                                const Value value) {
  validate_cell_indices(row, col);
  if (value.is_unset()) {
    return;
  }
  Cell& target_cell = get_cell(row, col);
  target_cell.set_value(value);
  for (Cell* cell: get_row(target_cell)) {
    if (!cell->is_set()) {
      bool cell_has_possible_values = cell->set_impossible(value);
      if (!cell_has_possible_values) {
        all_cells_have_possible_values_ = false;
      }
    }
  }
  for (Cell* cell: get_column(target_cell)) {
    if (!cell->is_set()) {
      bool cell_has_possible_values = cell->set_impossible(value);
      if (!cell_has_possible_values) {
        all_cells_have_possible_values_ = false;
      }
    }
  }
  for (Cell* cell: get_box(target_cell)) {
    if (!cell->is_set()) {
      bool cell_has_possible_values = cell->set_impossible(value);
      if (!cell_has_possible_values) {
        all_cells_have_possible_values_ = false;
      }
    }
  }
}

void SudokuGrid::set_cells_with_one_possible_value() {
  bool something_changed = true;
  while (something_changed) {
    something_changed = false;
    for (Cell& cell : cells_) {
      if (!cell.is_set() && cell.get_num_possible() == 1) {
        something_changed = true;
        for (Value value : cell.get_possible_values()) {
          // Will throw error if more than one possible value because you
          // can't call set_cell_value() on a cell that's already set.
          set_cell_value(cell.row, cell.col, value);
        }
      }
    }
  }
}

bool SudokuGrid::is_completed() const {
  for (const Cell& cell : cells_) {
    if (!cell.is_set()) {
      return false;
    }
  }
  return true;
}

bool SudokuGrid::all_cells_have_possible_values() const {
  return all_cells_have_possible_values_;
}

const Cell& SudokuGrid::get_cell_to_condition_on() const {
  int min_num_possible = INT_MAX;
  int min_row = 0;
  int min_col = 0;
  for (const Cell& cell : cells_) {
    if (!cell.is_set() && cell.get_num_possible() < min_num_possible) {
      min_num_possible = cell.get_num_possible();
      min_row = cell.row;
      min_col = cell.col;
    }
  }
  if (min_num_possible == INT_MAX) {
    throw NoUnsetCellsException();
  }
  return get_cell_const(min_row, min_col);  
}

void SudokuGrid::validate_cell_indices(int row, int col) const {
  if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
    throw CellIndicesOutOfRangeException();
  }
}

Cell& SudokuGrid::get_cell(int row, int col) {
  validate_cell_indices(row, col);
  return cells_[row * GRID_SIZE + col];
}

const Cell& SudokuGrid::get_cell_const(int row, int col) const {
  validate_cell_indices(row, col);
  return cells_[row * GRID_SIZE + col];
}

const std::array<Cell*, GRID_SIZE> SudokuGrid::get_row(const Cell& cell) {
  std::array<Cell*, GRID_SIZE> cells;
  for (int col = 0; col < GRID_SIZE; ++col) {
    cells[col] = &get_cell(cell.row, col);
  }
  return cells;
}

const std::array<Cell*, GRID_SIZE> SudokuGrid::get_column(const Cell& cell) {
  std::array<Cell*, GRID_SIZE> cells;
  for (int row = 0; row < GRID_SIZE; ++row) {
    cells[row] = &get_cell(row, cell.col);
  }
  return cells;
}

const std::array<Cell*, GRID_SIZE> SudokuGrid::get_box(const Cell& cell) {
  std::array<Cell*, GRID_SIZE> cells;
  const std::array<std::array<int, 3>, 3> groups = {
      std::array<int, 3> {0, 1, 2},
      std::array<int, 3> {3, 4, 5},
      std::array<int, 3> {6, 7, 8}};
  const int row_group = cell.row / 3;
  const int col_group = cell.col / 3;
  int i = 0;
  for (int row : groups[row_group]) {
    for (int col : groups[col_group]) {
      cells[i] = &get_cell(row, col);
      ++i;
    }
  }
  return cells;
}

std::ostream& operator<<(std::ostream& os, const SudokuGrid& grid) {
  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      os << grid.get_cell_const(row, col);
      if (col == 2 || col == 5){
        os << '|';
      }
    }
    os << '\n';
    if (row == 2 || row == 5){
      os << "---+---+---\n";
    }
  }
  return os;
}
