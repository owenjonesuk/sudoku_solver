#include <assert.h>
#include <fstream>
#include "sudokugrid.hpp"


SudokuGrid::SudokuGrid() {
}

SudokuGrid::SudokuGrid(const SudokuGrid& other) {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      setCellValue(row, col, other.grid_[row][col].getValue());
    }
  }
}

SudokuGrid::SudokuGrid(std::string file_location) {
  std::ifstream file(file_location);
  if (!file.is_open()) {
    std::cout << "Failed to open file " << file_location << "\n";
  } else {
    std::string line;
    int val;
    for (int row = 0; row < GRID_SIZE; row++) {
      getline(file, line);
      for (int col = 0; col < GRID_SIZE; col++) {
        if (col <= line.length()) {
          setCellValue(row, col, Value(line[col]));
        }
      }
    }
  }
}

bool SudokuGrid::setCellValue(const int row, const int col, const Value value) {
  if (value.isUnset()) {
    return true;
  }
  Cell& target_cell = grid_[row][col];
#ifdef DEBUG        
  std::cout << "(0) Setting the value " << convertValueToChar(value)
            << " for cell (" << row << "," << col << ")"
            << std::endl;
#endif
  target_cell.setValue(value);
  bool grid_valid = true;
  for (int i = 0; i < GRID_SIZE; i++) {
    Cell& cell = grid_[i][col];
    if (&cell != &target_cell && !cell.isSet()) {
#ifdef DEBUG        
      std::cout << "(1) Setting the value " << convertValueToChar(value)
                << " as impossible for cell (" << i << "," << col << ")"
                << std::endl;
#endif
      grid_valid = grid_valid & grid_[i][col].setImpossible(value);
    }
  }
  for (int j = 0; j < GRID_SIZE; j++) {
    Cell& cell = grid_[row][j];
    if (&cell != &target_cell && !cell.isSet()) {
#ifdef DEBUG        
      std::cout << "(2) Setting the value " << convertValueToChar(value)
                << " as impossible for cell (" << row << "," << j << ")"
                << std::endl;
#endif
      grid_valid = grid_valid & grid_[row][j].setImpossible(value);
    }
  }
  const std::array<std::array<int, 3>, 3> groups = {
      std::array<int, 3> {0, 1, 2},
      std::array<int, 3> {3, 4, 5},
      std::array<int, 3> {6, 7, 8}};
  const int row_group = row / 3;
  const int col_group = col / 3;
  for (int i : groups[row_group]) {
    for (int j : groups[col_group]) {
      Cell& cell = grid_[i][j];
      if (&cell != &target_cell && !cell.isSet()) {
#ifdef DEBUG        
        std::cout << "(3) Setting the value " << convertValueToChar(value)
                  << " as impossible for cell (" << i << "," << j << ")"
                  << std::endl;
#endif
        grid_valid = grid_valid & grid_[i][j].setImpossible(value);
      }
    }
  }
  return grid_valid;
}

void SudokuGrid::setCellsWithOnePossibleValue() {
  bool something_changed = true;
  while (something_changed) {
    something_changed = false;
    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        Cell& cell = grid_[i][j];
        if (!cell.isSet() && cell.getNumPossible() == 1) {
          something_changed = true;
          int n = 0;
          for (Value value : grid_[i][j].getPossibleValues()) {
            setCellValue(i, j, value);
            n++;
          }
          assert(n == 1);
        }
      }
    }
  }
}

bool SudokuGrid::isCompleted() {
  for (auto& cell_row : grid_) {
    for (auto& cell : cell_row) {
      if (!cell.isSet()) {
        return false;
      }
    }
  }
  return true;
}

void SudokuGrid::branchAndAddToStack(std::stack<SudokuGrid>& stack) {
  int min_found = GRID_SIZE + 2;
  int min_found_i = -1;
  int min_found_j = -1;
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      if (!grid_[i][j].isSet()) {
        int num_possible = grid_[i][j].getNumPossible();
        if (num_possible < min_found) {
          min_found = num_possible;
          min_found_i = i;
          min_found_j = j;
        }
      }
    }
  }
  Cell& min_cell = grid_[min_found_i][min_found_j];
  stack.pop();
  for (Value value : min_cell.getPossibleValues()) {
    SudokuGrid new_grid = SudokuGrid(*this);
    new_grid.setCellValue(min_found_i, min_found_j, value);
    stack.push(new_grid);
  }
}

void SudokuGrid::print(std::ostream &os) {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      os << grid_[row][col];
      if (col == 2 || col == 5){
        os << '|';
      }
    }
    os << '\n';
    if (row == 2 || row == 5){
      os << "---+---+---\n";
    }
  }
}
