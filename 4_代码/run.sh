#!/bin/zsh

cmake -B build
cmake --build build --parallel 8
build/first/first
