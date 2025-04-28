#!/bin/bash

cmake -S . -B build -DEnableTest=OFF # default turn off unit test

ARCH=$(uname -m)

case "$ARCH" in
  x86_64|amd64) cmake --build build --parallel $(nproc);;
  arm64|aarch64) cmake --build build --parallel 16 ;;
  *) echo "未知架构: $ARCH"; exit 1 ;;
esac
# cd build/SuperMarketManagementSystem && ctest
./build/SuperMarketManagementSystem/SuperMarketManagementSystem
