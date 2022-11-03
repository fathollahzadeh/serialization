#!/usr/bin/env bash
SRC_DIR="src/main/cpp/benchmark"
DST_DIR="src/main/cpp/benchmark"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/SimpleObject.proto
