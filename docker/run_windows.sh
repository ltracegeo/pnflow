#!/bin/bash

USER_ID=$(id -u)
docker run --rm -it -v .:/volume --user ${USER_ID}:${USER_ID} pnflow-build-windows "$@"
