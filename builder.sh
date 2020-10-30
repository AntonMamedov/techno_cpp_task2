#! /bin/bash

cd ./filemetrics
mkdir build
cd build
cmake .. 
make

cd ../..

cd ./filemetrics_multithreaded
mkdir build
cd build
cmake .. 
make
cd ../..

cd ./multi_test
mkdir build
cd build
cmake ..
make

cd ../..

cd ./single_test
mkdir build
cd build
cmake ..
make
cd ../..

cd ./test
mkdir build
cd build
cmake ..
make
cd ../..
