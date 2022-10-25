#!/usr/bin/env bash
flatc_path="/home/saeed/Apps/flatc"

#$flatc_path --java --gen-mutable src/main/java/at/tugraz/tweet/flatbuffers/*.fbs


$flatc_path --java --gen-mutable --gen-object-api --filename-suffix FBS  src/main/java/at/tugraz/tweet/flatbuffers/*.fbs
