#!/usr/bin/env bash

flatc_path="/home/saeed/Apps/flatc"
SRC_DIR="src/main/cpp/benchmark/flatbuffers"

$flatc_path --cpp --gen-mutable --gen-object-api --filename-suffix FBS src/main/cpp/benchmark/flatbuffers/*.fbs



