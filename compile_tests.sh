#!/bin/bash

# Flags for make:
# CXX="ccache clang++" CXXFLAGS="-Qunused-arguments -fcolor-diagnostics <other flags...>" CCACHE_CPP2=yes

COMPILER="clang++ -std=c++11 -g"
# COMPILER="ccache clang++ -Qunused-arguments -fcolor-diagnostics -std=c++11 -g"

$COMPILER tests_all.cpp -c

$COMPILER value.cpp -c
$COMPILER value.o tests_all.o tests_value.cpp -o tests_value.exe
./tests_value.exe

$COMPILER cell.cpp -c
$COMPILER value.o cell.o tests_all.o tests_cell.cpp -o tests_cell.exe
./tests_cell.exe

$COMPILER sudokugrid.cpp -c
$COMPILER value.o cell.o sudokugrid.o tests_all.o tests_sudokugrid.cpp -o tests_sudokugrid.exe
./tests_sudokugrid.exe

$COMPILER solver.cpp -c
$COMPILER value.o cell.o sudokugrid.o solver.o tests_all.o tests_solver.cpp -o tests_solver.exe
./tests_solver.exe
