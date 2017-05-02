#!/bin/bash

COMPILER="clang++ -std=c++11 -g"
# COMPILER="ccache clang++ -Qunused-arguments -fcolor-diagnostics -std=c++11 -g"

$COMPILER value.cpp -c
$COMPILER cell.cpp -c
$COMPILER sudokugrid.cpp -c
$COMPILER solver.cpp -c
$COMPILER run.cpp solver.o sudokugrid.o cell.o value.o -o run
