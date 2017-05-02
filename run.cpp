#include "solver.hpp"


int main(int argv, char* argc[]) {
  unsigned int n = (argv == 3) ? std::atoi(argc[2]) : 1;
  if (argv == 2 || argv == 3) {
    std::vector<SudokuGrid> completed_grids =
      Solver::solve(std::string(argc[1]), n);
    for (const SudokuGrid& grid : completed_grids) {
      std::cout << "\n";
      std::cout << grid;
      std::cout << "\n";
    }
  }
  else {
    std::cout << "Need two or three arguments\n";
  }
  return 0;  
}
