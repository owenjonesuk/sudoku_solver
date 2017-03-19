#include <stack>
#include "sudokugrid.hpp"

SudokuGrid solveSudokuGrid(SudokuGrid start_grid) {
  std::stack<SudokuGrid> stack;
  stack.push(start_grid);
  while (!stack.empty()) {
    SudokuGrid& grid = stack.top();
    grid.setCellsWithOnePossibleValue();
    if (grid.isCompleted()) {
      break;
    }
    grid.branchAndAddToStack(stack);
  }
  if (stack.empty()) {
    throw "Failed to find a solution";
  }
  return SudokuGrid(stack.top());
}

int main(int argv, char* argc[]) {
  SudokuGrid sudoku_grid("grids/grid_solvable.txt");
  SudokuGrid completed_grid = solveSudokuGrid(sudoku_grid);
  completed_grid.print(std::cout);
  return 0;  
}