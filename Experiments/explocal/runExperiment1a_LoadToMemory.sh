#!/bin/bash

inDataPath=$1
platform=$2
nrow=$3
log_file_name=$4


for rp in {1..5}; do
    start=$(date +%s%N)
    SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                   -Dnrow=${nrow}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataLoadToMemory${platform}
                "
    echo $SCRIPT
    $SCRIPT
    end=$(date +%s%N)
    echo "Java,"${platform}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    

