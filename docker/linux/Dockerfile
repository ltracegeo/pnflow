FROM ubuntu:20.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    make \
    cmake \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

VOLUME /volume
WORKDIR /volume
