#!/usr/bin/env bash
flatc_path="/home/saeed/Desktop/flatbuffers-master/flatc"
$flatc_path --cpp --gen-mutable --gen-object-api --filename-suffix FBS -o src/serialization/header/flatbuffers src/serialization/source/flatbuffers/*.fbs
#mv *generated.h src/serialization/source/flatbuffers
#rm -rf edu