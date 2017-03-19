#include <stack>
#include "sudokugrid.hpp"

SudokuGrid solveSudokuGrid(SudokuGrid start_grid) {
  std::stack<SudokuGrid> stack;
  std::cout << "  got here 1" << std::endl;
  stack.push(start_grid);
  std::cout << "  got here 2" << std::endl;
  while (!stack.empty()) {
  std::cout << "  got here 3" << std::endl;
    SudokuGrid& grid = stack.top();
  std::cout << "  got here 4" << std::endl;
    grid.setCellsWithOnePossibleValue();
  std::cout << "  got here 5" << std::endl;
    if (grid.isCompleted()) {
  std::cout << "  got here 6" << std::endl;
      break;
    }
  std::cout << "  got here 7" << std::endl;
    grid.branchAndAddToStack(stack);
  std::cout << "  got here 8" << std::endl;
  }
  std::cout << "  got here 9" << std::endl;
  if (stack.empty()) {
    throw "Failed to find a solution";
  }
  return SudokuGrid(stack.top());
}

int main(int argv, char* argc[]) {
  SudokuGrid sudoku_grid("grids/grid_one_cell_missing.txt");
  std::cout << "got here 1" << std::endl;
  SudokuGrid completed_grid = solveSudokuGrid(sudoku_grid);
  std::cout << "got here 2" << std::endl;
  completed_grid.print(std::cout);
  std::cout << "got here 3" << std::endl;
  return 0;  
}