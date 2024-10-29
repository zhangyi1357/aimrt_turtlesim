#!/bin/bash

cmake -B build -DCMAKE_INSTALL_PREFIX=./build/install

cmake --build build --target install --parallel $(nproc)