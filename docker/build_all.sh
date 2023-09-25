#!/bin/bash

./docker/build_docker_images.sh
./docker/run_windows.sh ./build.sh -p Windows
./docker/run_linux.sh ./build.sh -p Linux
