#!/bin/bash
./clean.sh
cp ../build/src/pnm/pnflow/pnflow.lib .
x86_64-w64-mingw32-gcc -static-libgcc test.c -L../build/src/pnm/pnflow/ -I../src/pnm/pnflow/ -lpnflow
