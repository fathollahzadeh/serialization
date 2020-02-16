#!/usr/bin/env bash
SRC_DIR="src/serialization/source/proto"
DST_DIR="src/serialization/source/proto"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/TweetStatusP.proto