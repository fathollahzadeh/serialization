#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
seq_rand=$6
log_file_name=$7
randomDataPath=$8

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="$jCMD  -DinDataPath=${inDataPath}.${method}Java\
                   -Dnrow=${nrow}\
                   -DseqRand=${seq_rand}\
                   -DrandomDataPath=${randomDataPath}\
                   -Dmethod=${method}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataReadIO${platform}
            "
    if [ "$task_set" = true ] ; then
        SCRIPT="taskset -c 0 $SCRIPT"
    fi
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"Java,Java,"${task_set}",IO,"${platform}","${seq_rand}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done
