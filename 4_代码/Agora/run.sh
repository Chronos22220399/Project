#!/bin/bash

cmake -S . -B build
cmake --build build --parallel $(nproc) 
cd build/SuperMarket && ctest
