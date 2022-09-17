#!/bin/bash

cd ..
cd tests
mkdir build
cd build
cmake ..
make
# run each test
for file in *.out
do
    ./$file
done
# remove each test before next compilation
for file in *.out
do
    rm $file
done