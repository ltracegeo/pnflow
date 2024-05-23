#!/bin/bash

function usage {
    cat <<EOF
Usage: ./build.sh --help
       ./build.sh [-p <Windows|Linux>] [--tests]

Automate pnflow build

Options:
    -h, --help      Display this message and exit
    -e, --exe       Build as executable instead of library
    -p, --platfrom  Target system (default: Windows)
    -t, --tests     Also build tests
    -d, --debug     Build with debug symbols
EOF
}

function get_args {
    ARG_BUILD_AS_EXE=false
    ARG_PLATFORM="Windows"
    ARG_BUILD_TESTS=false
    ARG_DEBUG=false

    while (( $# )); do
        case $1 in
            -h|--help)
                usage
                exit 0
                ;;
            -e|--exe)
                ARG_BUILD_AS_EXE=true
                ;;
            -p|--platform)
                if [[ -z $2 ]]; then
                    echo "error: missing platform argument"
                    exit 1
                fi
                ARG_PLATFORM=$2
                shift
                ;;
            -t|--tests)
                ARG_BUILD_TESTS=true
                ;;
            -d|--debug)
                ARG_DEBUG=true
                ;;
            *)
                echo "error: invalid parameter \"$1\""
                exit
                ;;
        esac
        shift
    done
}

function process_args {
    PNFLOW_WINDOWS="ON"
    BUILD_CMAKE_PARAMS=""
    TESTS_GCC_PARAMS=""

    if ${ARG_BUILD_AS_EXE}; then
        DPNFLOW_AS_LIB="OFF"
    else
        DPNFLOW_AS_LIB="ON"
    fi

    if [[ ${ARG_PLATFORM} == "Windows" ]]; then
        PNFLOW_WINDOWS="ON"
        BUILD_DIR=win
    elif [[ ${ARG_PLATFORM} == "Linux" ]]; then
        PNFLOW_WINDOWS="OFF"
        BUILD_DIR=linux
    else
        echo "error: unsupported platform ${ARG_PLATFORM}"
        exit 1
    fi

    if ${ARG_DEBUG}; then
        BUILD_CMAKE_PARAMS+="-DCMAKE_BUILD_TYPE=Debug "
        TESTS_GCC_PARAMS+="-ggdb "
    fi
}

function build_pnflow {(
    mkdir -p build/${BUILD_DIR}
    cd build/${BUILD_DIR}
    cmake -G "Unix Makefiles" -DPNFLOW_WINDOWS=${PNFLOW_WINDOWS} -DPNFLOW_AS_LIB=${DPNFLOW_AS_LIB} ${BUILD_CMAKE_PARAMS} ../..
    make
    if [[ ${ARG_PLATFORM} == "Windows" ]]; then
        cp ./src/pnm/pnflow/pnflow.lib ../../python/pnflow/
    elif [[ ${ARG_PLATFORM} == "Linux" ]]; then
        cp ./src/pnm/pnflow/libpnflow.so ../../python/pnflow/
    fi
)}

function build_tests {(
    cd teste/c/
    if [[ ${ARG_PLATFORM} == "Windows" ]]; then
        cp ../../build/${BUILD_DIR}/src/pnm/pnflow/pnflow.lib .
        x86_64-w64-mingw32-gcc -static-libgcc test.c -L../../build/${BUILD_DIR}/src/pnm/pnflow/ -I../../src/pnm/pnflow/ -lpnflow
    elif [[ ${ARG_PLATFORM} == "Linux" ]]; then
        gcc -static-libgcc test.c -L../../build/${BUILD_DIR}/src/pnm/pnflow/ -I../../src/pnm/pnflow/ -lpnflow -Wl,-rpath,${PWD}/../../build/${BUILD_DIR}/src/pnm/pnflow/ ${TESTS_GCC_PARAMS}
    fi
)}

function run {
    get_args "$@"
    process_args

    build_pnflow
    if ${ARG_BUILD_TESTS}; then
        build_tests
    fi
}

run "$@"
