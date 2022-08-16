#!/bin/bash


inDataPath=$1
platform=$2
task_set=$3
seq_rand=$4
nrow=$5
log_file_name=$6
randomDataPath=$7


for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                   -DrandomDataPath=${randomDataPath}\
                   -Dnrow=${nrow}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataLoadToMemory${platform}
                "
    if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
    fi            
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo "Java,"${platform}","${task_set}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    