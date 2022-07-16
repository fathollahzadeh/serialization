#!/bin/bash

# prepare data for Java experiments

# cleanup
rm -rf data/tweets.bin
rm -rf data/tweets.bin.index

inDataPath="data/tweets.txt"
outDataPathJava="data/tweets.jbin"
nrow=$(sed -n '$=' $inDataPath)

SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                -DoutDataPath=${outDataPathJava}\
                -Dnrow=${nrow}\
                -cp ./SerializationJava.jar at.tugraz.experiments.DataPrepare
        "
echo $SCRIPT
time $SCRIPT

# prepare data for C++ experiments

# prepare data for Rust experiments