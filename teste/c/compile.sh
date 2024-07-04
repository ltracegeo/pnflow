#!/bin/bash
./clean.sh
cp ../../build/win/src/pnm/pnflow/pnflow.lib .
x86_64-w64-mingw32-g++ -static-libgcc test.cpp -L../../build/win/src/pnm/pnflow/ -I../../src/pnm/pnflow/ -lpnflow
