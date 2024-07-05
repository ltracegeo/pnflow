FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    wget \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://cmake.org/files/v3.16/cmake-3.16.0-Linux-x86_64.sh && \
    chmod a+x cmake-3.16.0-Linux-x86_64.sh && \
    ./cmake-3.16.0-Linux-x86_64.sh --skip-license --prefix=/ && \
    rm ./cmake-3.16.0-Linux-x86_64.sh

RUN apt-get remove --purge -y wget && \
    apt-get autoremove -y

VOLUME /volume
WORKDIR /volume
