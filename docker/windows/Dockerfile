FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    mingw-w64 \
    make \
    cmake \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

VOLUME /volume
WORKDIR /volume
