#!/bin/bash

COMPILER=clang++
$COMPILER -std=c++11 -g tests_all.cpp -c

$COMPILER -std=c++11 -g value.cpp -c
$COMPILER -std=c++11 -g value.o tests_all.o tests_value.cpp -o tests_value.exe
./tests_value.exe

$COMPILER -std=c++11 -g cell.cpp -c
$COMPILER -std=c++11 -g value.o cell.o tests_all.o tests_cell.cpp -o tests_cell.exe
./tests_cell.exe

$COMPILER -std=c++11 -g sudokugrid.cpp -c
$COMPILER -std=c++11 -g value.o cell.o sudokugrid.o tests_all.o tests_sudokugrid.cpp -o tests_sudokugrid.exe
./tests_sudokugrid.exe
