#!/usr/bin/env bash
SRC_DIR="serialization/source/proto"
DST_DIR="serialization/source/proto"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/TweetStatusP.proto

mv serialization/source/proto/TweetStatusP.pb.h serialization/header/proto/TweetStatusP.pb.h