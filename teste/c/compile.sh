#!/bin/bash
./clean.sh
LIB_PATH=$(realpath ../../python/pnflow/)
cp ${LIB_PATH}/pnflow.lib .
x86_64-w64-mingw32-g++ -static-libgcc test.cpp -L${LIB_PATH} -I../../src/pnm/pnflow/ -lpnflow
