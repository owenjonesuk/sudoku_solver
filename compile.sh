#g++.exe -std=c++11 cell.cpp -c
#g++.exe -std=c++11 sudokugrid.cpp -c
#g++.exe -std=c++11 solvesudoku.cpp sudokugrid.o cell.o -o solvesudokugrid
clang++ -std=c++11 cell.cpp -c
clang++ -std=c++11 sudokugrid.cpp -c
clang++ -std=c++11 solvesudoku.cpp sudokugrid.o cell.o -o solvesudokugrid
