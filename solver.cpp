#include <stack>
#include <vector>
#include "solver.hpp"




static void condition_on_a_cell(std::stack<SudokuGrid>& stack) {
  const SudokuGrid grid = stack.top();
  stack.pop();
  const Cell& cell = grid.get_cell_to_condition_on();
  for (Value value : cell.get_possible_values()) {
    stack.emplace(SudokuGrid(grid));
    stack.top().set_cell_value(cell.row, cell.col, value);
  }
}

/// When this function returns either the stack is empty, which means the
/// depth-first search is over, or the grid on to top of the stack is a solved
/// grid
static void find_next_solution(std::stack<SudokuGrid>& stack) {
  while (!stack.empty()) {
    SudokuGrid& grid = stack.top();
    grid.set_cells_with_one_possible_value();
    if (grid.is_completed()) {
      return;
    }
    else if (!grid.all_cells_have_possible_values()) {
      stack.pop();
    }
    else {
      condition_on_a_cell(stack);
    }
  }
}

std::vector<SudokuGrid> Solver::solve(const std::string& file_location,
                                      unsigned int n) {
  std::vector<SudokuGrid> solutions;
  solutions.reserve(n);
  std::stack<SudokuGrid> stack;
  stack.emplace(SudokuGrid(file_location));
  // Do a depth-first search through the space of all partially completed grids
  // that are valid that can be reached from the grid we have pushed onto the
  // stack. 
  find_next_solution(stack);
  while (!stack.empty()) {
    solutions.push_back(stack.top());
    stack.pop();
    if (n != 0 && solutions.size() >= n) {
      break;
    }
    find_next_solution(stack);
  }
  return solutions;
}
