#! /bin/bash

cd ./filemetrics
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang-10
make
ln

cd ../..

cd ./filemetrics_multithreaded
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang-10
make
ln

cd ../..

cd ./multi_thread_test
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang-10
make
ln

cd ../..

cd ./non_thread_test
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang-10
make
ln

cd ../..

cd ./test
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang-10
make
ln

cd ../..
