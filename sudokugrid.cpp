#include <assert.h>
#include <iostream>
#include <fstream>
#include "sudokugrid.hpp"

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.getValue();
  return os;
}

SudokuGrid::SudokuGrid() {
}

SudokuGrid::SudokuGrid(const SudokuGrid& other) {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      setCellValue(row, col, other.cell_[row][col].getValue());
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
        Cell::Value value =  Cell::UNSET;
        if (col <= line.length()) {
          switch (line[col]) {
            case '1': {
              value = Cell::V1;
              break;
            }
            case '2': {
              value = Cell::V2;
              break;
            }
            case '3': {
              value = Cell::V3;
              break;
            }
            case '4': {
              value = Cell::V4;
              break;
            }
            case '5': {
              value = Cell::V5;
              break;
            }
            case '6': {
              value = Cell::V6;
              break;
            }
            case '7': {
              value = Cell::V7;
              break;
            }
            case '8': {
              value = Cell::V8;
              break;
            }
            case '9': {
              value = Cell::V9;
              break;
            }
          }
        }
        setCellValue(row, col, value);
      }
    }
  }
}

bool SudokuGrid::setCellValue(int row, int col, Cell::Value value) {
  cell_[row][col].setValue(value);
  bool all_possible = true;
  for (int i = 0; i < GRID_SIZE; i++) {
    if (i != row) {
      all_possible = all_possible & cell_[i][col].setImpossible(value);
    }
    if (i != col) {
      all_possible = all_possible & cell_[row][i].setImpossible(value);
    }
  }
  return all_possible;
}

void SudokuGrid::setCellsWithOnePossibleValue() {
  bool something_changed = true;
  while (something_changed) {
    something_changed = false;
    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        if (cell_[i][j].getNumPossible() == 1) {
          something_changed = true;
          int n = 0;
          for (Cell::Value value : cell_[i][j].getPossibleValues()) {
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
  for (auto& cell_row : cell_) {
    for (auto& cell : cell_row) {
      if (cell.getNumPossible() != 1) {
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
      if (!cell_[i][j].isSet()) {
        int num_possible = cell_[i][j].getNumPossible();
        if (num_possible < min_found) {
          min_found = num_possible;
          min_found_i = i;
          min_found_j = j;
        }
      }
    }
  }
  Cell& min_cell = cell_[min_found_i][min_found_j];
  stack.pop();
  for (Cell::Value value : min_cell.getPossibleValues()) {
    SudokuGrid new_grid = SudokuGrid(*this);
    new_grid.setCellValue(min_found_i, min_found_j, value);
    stack.push(new_grid);
  }
}

void SudokuGrid::Print() {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      std::cout << cell_[row][col];
      if (col == 2 || col == 5){
        std::cout << '|';
      }
    }
    std::cout << '\n';
    if (row == 2 || row == 5){
      std::cout << "---+---+---\n";
    }
  }
}

// bool SudokuGrid::CheckValidity() {
    
    
// }