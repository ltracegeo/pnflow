#!/bin/bash
mkdir -p build
cd build
cmake -DPNFLOW_WINDOWS=ON ..
make
