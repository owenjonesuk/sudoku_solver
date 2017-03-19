#!/bin/bash

COMPILER=clang++
$COMPILER -std=c++11 -g value.cpp -c
$COMPILER -std=c++11 -g cell.cpp -c
$COMPILER -std=c++11 -g sudokugrid.cpp -c
$COMPILER -std=c++11 -g solvesudoku.cpp sudokugrid.o cell.o value.o -o solvesudokugrid
