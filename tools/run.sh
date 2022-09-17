#!/bin/sh

cd ..
mkdir build
cd build
cmake ..
make
./sudoku
rm sudoku