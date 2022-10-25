#!/usr/bin/env bash
SRC_DIR="src/main/java/at/tugraz/tweet/proto"
DST_DIR="src/main/java"

#/home/saeed/Documents/GitHub/serialization/src/main/java/at/tugraz/tweet/proto/

protoc -I=$SRC_DIR --java_out=$DST_DIR $SRC_DIR/TweetStatusP.proto
