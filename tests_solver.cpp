#include "catch.hpp"
#include "solver.hpp"


const std::string grid_solved_string =
  "534|678|912\n"
  "672|195|348\n"
  "198|342|567\n"
  "---+---+---\n"
  "859|761|423\n"
  "426|853|791\n"
  "713|924|856\n"
  "---+---+---\n"
  "961|537|284\n"
  "287|419|635\n"
  "345|286|179\n";

TEST_CASE ("Solve a solved grid", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_solved.txt", 0);
  REQUIRE(grids.size() == 1);
  std::ostringstream output;
  output << grids[0];
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Solve a grid with one blank cell", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_one_cell_missing.txt", 0);
  REQUIRE(grids.size() == 1);
  std::ostringstream output;
  output << grids[0];
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Solve a normal puzzle grid", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_solvable.txt", 0);
  REQUIRE(grids.size() == 1);
  std::ostringstream output;
  output << grids[0];
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Cannot solve an unsolvable grid", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_unsolvable.txt", 0);
  REQUIRE(grids.size() == 0);
}

TEST_CASE ("Finds two solutions when they exist", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_two_solutions.txt", 0);
  REQUIRE(grids.size() == 2);
}

TEST_CASE ("Find just one solution when asked", "[solver]") {
  std::vector<SudokuGrid> grids = Solver::solve("grids/grid_two_solutions.txt", 1);
  REQUIRE(grids.size() == 1);
}
