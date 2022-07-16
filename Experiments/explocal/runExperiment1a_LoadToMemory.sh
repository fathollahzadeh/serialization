#!/bin/bash

inDataPath=$1
platform=$2
seqRand=$3
nrow=$4
log_file_name=$5
randomDataPath=$6


for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                   -DseqRand=${seqRand}\
                   -DrandomDataPath=${randomDataPath}\
                   -Dnrow=${nrow}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataLoadToMemory${platform}
                "
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo "Java,"${platform}","${nrow}","${seqRand}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    

