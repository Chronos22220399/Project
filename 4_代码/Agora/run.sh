#!/bin/bash

cmake -S . -B build
cmake --build build --parallel $(nproc) 
# cd build/SuperMarketManagementSystem && ctest
./build/SuperMarketManagementSystem/SuperMarketManagementSystem
