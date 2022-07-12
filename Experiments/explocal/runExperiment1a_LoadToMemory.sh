#!/bin/bash

inDataPath=$1
nrow=$2
log_file_name=$3

# write header to log file
echo "language,time" >>results/$log_file_name.dat

for rp in {1..5}; do
    start=$(date +%s%N)
    SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                   -Dnrow=${nrow}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataLoadToMemory
                "
    echo $SCRIPT
    $SCRIPT
    end=$(date +%s%N)
    echo "Java,"$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    

