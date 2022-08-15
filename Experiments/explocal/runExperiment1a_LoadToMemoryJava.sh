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
    SCRIPT="./cppbin/DataLoadToMemory${platform} ${inDataPath} ${seq_rand} ${nrow} ${randomDataPath}"
    if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
    fi            
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo "CPP,"${platform}","${task_set}","${nrow}","${seq_rand}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    

