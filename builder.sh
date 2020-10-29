#! /bin/bash

cd filemetrics
mkdir build
cd build
cmake ..
make

cd ../..

cd filemetrics_multithreaded
mkdir build
cd build
cmake ..
make

cd ../..

cd multi_thread_test
mkdir build
cd build
cmake ..
make

cd ../..

cd non_thread_test
mkdir build
cd build
cmake ..
make

cd ../..

cd test
mkdir build
cd build
cmake ..
make

cd ../..

cd test_dirs
mkdir test_dir_1

cd ..