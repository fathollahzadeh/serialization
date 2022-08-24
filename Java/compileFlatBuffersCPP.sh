#!/usr/bin/env bash
flatc_path="/home/saeed/Apps/serialization_packages/Linux.flatc.binary.clang++-9/flatc"
$flatc_path --cpp --gen-mutable --gen-object-api --filename-suffix FBS -o serialization/header/flatbuffers serialization/source/flatbuffers/*.fbs
#mv *generated.h src/serialization/source/flatbuffers
#rm -rf edu