#!/bin/bash
./clean.sh
# cp ../../build/linux/src/pnm/pnflow/libpnflow.so .
LIB_PATH=$(realpath ../../build/linux/src/pnm/pnflow/)
g++ -Wl,-rpath,${LIB_PATH} -static-libgcc test.cpp -L../../build/linux/src/pnm/pnflow/ -I../../src/pnm/pnflow/ -lpnflow
