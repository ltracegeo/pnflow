#!/bin/bash
./clean.sh
# cp ../../build/linux/src/pnm/pnflow/libpnflow.so .
LIB_PATH=$(realpath ../../python/pnflow/)
g++ -Wl,-rpath,${LIB_PATH} -static-libgcc test.cpp -L../../python/pnflow/ -I../../src/pnm/pnflow/ -lpnflow
