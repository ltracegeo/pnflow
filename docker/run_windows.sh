#!/bin/bash

docker run --rm -it -v .:/volume --user 1000:1000 pnflow-build-windows "$@"
