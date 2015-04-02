#!/bin/bash

SCRIPT_PATH=$(cd $(dirname $0) ; pwd -P)
BUILD_PATH=$SCRIPT_PATH/build

[ ! -d $BUILD_PATH ] && mkdir -p $BUILD_PATH
[ ! -d $BUILD_PATH/CMakeFiles ] && (cd $BUILD_PATH; cmake -G Ninja $SCRIPT_PATH)

(cd $BUILD_PATH; ninja "$@")

