#!/usr/bin/env bash
SRC_DIR="src/main/cpp/serialization/source/proto"
DST_DIR="src/main/cpp/serialization/source/proto"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/TweetStatusP.proto
mv "$DST_DIR/TweetStatusP.pb.h" src/main/cpp/serialization/header/proto/
