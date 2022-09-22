#!/bin/sh

cd ..
mkdir build
cd build
cmake ..
cmake --build .
./sudoku
rm sudoku