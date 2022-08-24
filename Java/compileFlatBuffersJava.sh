#!/usr/bin/env bash
flatc_path="/home/saeed/Desktop/flatbuffers-master/flatc"
$flatc_path --java --gen-mutable src/main/java/edu/bu/tweet/flatbuffers/*.fbs
mv edu/bu/tweet/flatbuffers/* src/main/java/edu/bu/tweet/flatbuffers
rm -rf edu