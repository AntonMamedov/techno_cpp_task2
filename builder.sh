#! /bin/bash

cd ./filemetrics
mkdir build
cd build
cmake ..
make
ln

cd ../..

cd ./filemetrics_multithreaded
mkdir build
cd build
cmake ..
make
ln

cd ../..

cd ./multi_thread_test
mkdir build
cd build
cmake ..
make
ln

cd ../..

cd ./non_thread_test
mkdir build
cd build
cmake ..
make
ln

cd ../..

cd ./test
mkdir build
cd build
cmake ..
make
ln

cd ../..
