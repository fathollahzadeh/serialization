#!/usr/bin/env bash

flatc_path="/home/saeed/Apps/flatc"
SRC_DIR="src/main/cpp/serialization/source/flatbuffers"
DST_DIR="src/main/cpp/serialization/source/flatbuffers"

/home/saeed/Apps/flatc --cpp --gen-mutable --gen-object-api --filename-suffix FBS  src/main/cpp/serialization/source/flatbuffers/*.fbs

#mv *generated.h src/serialization/source/flatbuffers
#rm -rf edu



