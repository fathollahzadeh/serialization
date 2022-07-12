#!/bin/bash

# prepare data for Java experiments

nrow=100000

# cleanup
rm -rf data/tweets.bin
rm -rf data/tweets.bin.index

SCRIPT="$jCMD  -DinDataPath=data/tweets.txt\
                -DoutDataPath=data/tweets.bin\
                -Dnrow=${nrow}\
                -cp ./SerializationJava.jar at.tugraz.experiments.DataPrepare
        "
echo $SCRIPT
time $SCRIPT

# prepare data for C++ experiments

# prepare data for Rust experiments