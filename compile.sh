#!/bin/bash

COMPILER=clang++
$COMPILER -std=c++11 cell.cpp -c
$COMPILER -std=c++11 sudokugrid.cpp -c
$COMPILER -std=c++11 solvesudoku.cpp sudokugrid.o cell.o -o solvesudokugrid
