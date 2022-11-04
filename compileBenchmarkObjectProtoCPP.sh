#!/usr/bin/env bash
SRC_DIR="src/main/cpp/benchmark/proto"
DST_DIR="src/main/cpp/benchmark/proto"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/SimpleObject.proto
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/ComplexObjectL1.proto
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/ComplexObjectL2.proto
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/ComplexObjectL3.proto
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/ComplexObjectL4.proto

