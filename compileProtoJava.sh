#!/usr/bin/env bash
SRC_DIR="src/main/java/edu/bu/tweet/proto"
DST_DIR="src/main/java"

protoc -I=$SRC_DIR --java_out=$DST_DIR $SRC_DIR/TweetStatusP.proto