#!/bin/bash
export ARCH=arm
export CROSS_COMPILE=arm-bytebox-linux-gnueabihf-

docker run -v $(pwd):/playground:rw  mengdemao/bytebox-compiler:latest './build.sh all'