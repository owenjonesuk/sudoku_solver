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

TEST_CASE ("Create blank sudoku grid", "[sudokugrid]") {
  SudokuGrid grid;
  std::ostringstream output;
  output << grid;
  REQUIRE(output.str() == grid_blank_string);
}

TEST_CASE ("Construct one sudoku grid from another", "[sudokugrid]") {
  const SudokuGrid grid1("grids/grid_solved.txt");
  SudokuGrid grid2(grid1);
  std::ostringstream output;
  output << grid2;
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Read blank sudoku grid from file", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_blank.txt");
  std::ostringstream output;
  output << grid;
  REQUIRE(output.str() == grid_blank_string);
}

TEST_CASE ("Read solved sudoku grid from file", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_solved.txt");
  std::ostringstream output;
  output << grid;
  REQUIRE(output.str() == grid_solved_string);
}

TEST_CASE ("Abort when the file cannot be found", "[sudokugrid]") {
  REQUIRE_THROWS_AS(SudokuGrid("grids/a.txt"), FailedToOpenFileException);
}

TEST_CASE ("Cannot set a cell with out-of-range indices", "[sudokugrid]") {
  SudokuGrid grid;
  REQUIRE_THROWS_AS(grid.set_cell_value(-1, 0, Value()),
                    CellIndicesOutOfRangeException);
  REQUIRE_THROWS_AS(grid.set_cell_value(0, -1, Value()),
                    CellIndicesOutOfRangeException);
  REQUIRE_THROWS_AS(grid.set_cell_value(GRID_SIZE + 1, 0, Value()),
                    CellIndicesOutOfRangeException);
  REQUIRE_THROWS_AS(grid.set_cell_value(0, GRID_SIZE + 1, Value()),
                    CellIndicesOutOfRangeException);
}

TEST_CASE ("Set a cell's value", "[sudokugrid]") {
  std::vector<Value> all_values_with_unset(Value::all_values);
  all_values_with_unset.emplace(all_values_with_unset.cbegin(), Value());
  for (Value value : all_values_with_unset) {
    SudokuGrid grid;
    grid.set_cell_value(0, 0, value);
    std::ostringstream output;
    output << grid;
    std::ostringstream expected_output;
    expected_output << value;
    REQUIRE(output.str()[0] == expected_output.str()[0]);
  }
}

TEST_CASE ("Setting a cell's value removes that value from possible values for appropriate other cells",
           "[sudokugrid]") {
  SudokuGrid grid;
  Value value = Value::all_values[0];
  grid.set_cell_value(0, 0, value);
  for (int j = 1; j < GRID_SIZE; ++j) {
    REQUIRE_THROWS_AS(grid.set_cell_value(0, j, value),
                      ImpossibleValueException);
  }
  for (int i = 1; i < GRID_SIZE; ++i) {
    REQUIRE_THROWS_AS(grid.set_cell_value(i, 0, value),
                      ImpossibleValueException);
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (!(i == 0 && j == 0)) {
        REQUIRE_THROWS_AS(grid.set_cell_value(i, j, value),
                          ImpossibleValueException);
      }
    }
  }
}

TEST_CASE ("Set cells with only one possible value", "[sudokugrid]") {
  SudokuGrid grid1("grids/grid_one_cell_missing.txt");
  grid1.set_cells_with_one_possible_value();
  std::ostringstream output1;
  output1 << grid1;
  REQUIRE(output1.str() == grid_solved_string);
  
  SudokuGrid grid2;
  grid2.set_cell_value(0, 1, Value::all_values[1]);
  grid2.set_cell_value(0, 2, Value::all_values[2]);
  grid2.set_cell_value(1, 0, Value::all_values[3]);
  grid2.set_cell_value(1, 1, Value::all_values[4]);
  grid2.set_cell_value(1, 2, Value::all_values[5]);
  grid2.set_cell_value(2, 0, Value::all_values[6]);
  grid2.set_cell_value(2, 1, Value::all_values[7]);
  grid2.set_cell_value(2, 2, Value::all_values[8]);
  grid2.set_cells_with_one_possible_value();
  std::ostringstream output2;
  output2 << grid2;
  std::ostringstream expected_output;
  expected_output << Value::all_values[0];
  REQUIRE(output2.str()[0] == expected_output.str()[0]);
}

TEST_CASE ("Determine that a grid is completed", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_solved.txt");
  REQUIRE(grid.is_completed());
}

TEST_CASE ("Determine that a grid is not completed", "[sudokugrid]") {
  std::array<std::string, 3> file_locations = {
      std::string("grids/grid_blank.txt"),
      std::string("grids/grid_solvable.txt"),
      std::string("grids/grid_one_cell_missing.txt")};
  for (std::string file_location : file_locations) {
    SudokuGrid grid(file_location);
    REQUIRE(!grid.is_completed());
  }
}

TEST_CASE ("Check if all cells have possible values", "[sudokugrid]") {
  std::array<std::string, 5> file_locations = {
      std::string("grids/grid_blank.txt"),
      std::string("grids/grid_solvable.txt"),
      std::string("grids/grid_two_solutions.txt"),
      std::string("grids/grid_one_cell_missing.txt"),
      std::string("grids/grid_solved.txt")};
  for (std::string file_location : file_locations) {
    SudokuGrid grid(file_location);
    REQUIRE(grid.all_cells_have_possible_values());
  }
  SudokuGrid grid("grids/grid_unsolvable.txt");
  REQUIRE(!grid.all_cells_have_possible_values());
}

TEST_CASE ("Abort when trying to get a cell to condition on in a solved grid",
           "[sudokugrid]") {
  SudokuGrid grid("grids/grid_solved.txt");
  REQUIRE_THROWS_AS(grid.get_cell_to_condition_on(), NoUnsetCellsException);
}

TEST_CASE ("Get a cell to condition on", "[sudokugrid]") {
  SudokuGrid grid("grids/grid_one_cell_missing.txt");
  Cell cell = grid.get_cell_to_condition_on();
  REQUIRE(!cell.is_set());
  REQUIRE(cell.row == 8);
  REQUIRE(cell.col == 8);
}
