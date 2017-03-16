#!/bin/bash

COMPILER=clang++
$COMPILER -std=c++11 tests_all.cpp -c
$COMPILER -std=c++11 cell.cpp -c
$COMPILER -std=c++11 cell.o tests_all.o tests_cell.cpp -o tests_cell.exe
#$COMPILER -std=c++11 sudokugrid.cpp -c
#$COMPILER -std=c++11 tests_all.o tests_sudokugrid.cpp -o tests_sudokugrid.exe
./tests_cell.exe
#./tests_sudokugrid.exe
