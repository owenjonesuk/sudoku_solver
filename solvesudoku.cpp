#include <stack>
#include "sudokugrid.hpp"

SudokuGrid solveSudokuGrid(SudokuGrid& start) {
  std::stack<SudokuGrid> stack;
  bool found_solution = false;
  stack.push(start);
  while (!stack.empty() && !found_solution) {
    SudokuGrid& grid = stack.top();
    grid.setCellsWithOnePossibleValue();
    if (grid.isCompleted()) {
      break;
    }
    grid.branchAndAddToStack(stack);
  }
  return SudokuGrid(stack.top());
}

int main(int argv, char* argc[]) {
  SudokuGrid sudoku_grid_2("grid_easy.txt");
  SudokuGrid completed_grid = solveSudokuGrid(sudoku_grid_2);
  completed_grid.Print();
  return 0;  
}