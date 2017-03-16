#include <stack>
#include <string>
#include "cell.hpp"

class SudokuGrid {
private:
  std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE> cell_;
public:
  SudokuGrid();
  SudokuGrid(const SudokuGrid&);
  SudokuGrid(std::string);
  bool setCellValue(int, int, Value);
  void setCellsWithOnePossibleValue();
  bool isCompleted();
  void branchAndAddToStack(std::stack<SudokuGrid>&);
  void Print();
private:
  bool CheckValidity();
};