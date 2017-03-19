#include "catch.hpp"
#include "sudokugrid.hpp"

const std::string grid_blank_string = 
    "...|...|...\n"
    "...|...|...\n"
    "...|...|...\n"
    "---+---+---\n"
    "...|...|...\n"
    "...|...|...\n"
    "...|...|...\n"
    "---+---+---\n"
    "...|...|...\n"
    "...|...|...\n"
    "...|...|...\n";

const std::string grid_solved_string =
    "391|286|574\n"
    "487|359|126\n"
    "652|714|839\n"
    "---+---+---\n"
    "875|431|692\n"
    "213|967|485\n"
    "964|528|713\n"
    "---+---+---\n"
    "149|673|258\n"
    "538|142|967\n"
    "726|895|341\n";

TEST_CASE ("Create blank sudoku grid correctly", "[sudokugrid]") {
  SudokuGrid grid;
  std::ostringstream output;
  grid.print(output);
  REQUIRE(output.str() == grid_blank_string);
}

TEST_CASE ("Read grid_blankk sudoku grid from file correctly", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_blank.txt");
  std::ostringstream output;
  grid.print(output);
  REQUIRE(output.str() == grid_blank_string);
}

TEST_CASE ("Read solved sudoku grid from file correctly", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_solved.txt");
  std::ostringstream output;
  grid.print(output);
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Construct one sudoku grid from another", "[sudokugrid]") {
  SudokuGrid grid1("grids/grid_solved.txt");
  SudokuGrid grid2(grid1);
  std::ostringstream output;
  grid2.print(output);
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Sets a cell's value", "[sudokugrid]") {
  for (Value value : Value::all_values) {
    SudokuGrid grid;
    grid.setCellValue(0, 0, value);
    std::ostringstream output;
    grid.print(output);
    std::ostringstream expected_output;
    expected_output << value;
    REQUIRE(output.str()[0] == expected_output.str()[0]);
  }
}

TEST_CASE ("When setting a cell's value, remove this value from possible values for appropriate other cells", "[sudokugrid]") {
}

TEST_CASE ("Determine that a grid is completed", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_solved.txt");
  REQUIRE(grid.isCompleted());
}

TEST_CASE ("Determine that a grid is not completed", "[sudokugrid]") {
  std::array<std::string, 3> file_locations = {
      std::string("grids/grid_blank.txt"),
      std::string("grids/grid_solvable.txt"),
      std::string("grids/grid_one_cell_missing.txt")};
  for (std::string file_location : file_locations) {
    SudokuGrid grid(file_location);
    REQUIRE(!grid.isCompleted());
  }
}
