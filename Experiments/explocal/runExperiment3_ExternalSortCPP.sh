#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4
task_set=$5
log_file_name=$6
chunk_size=100000

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="./cppbin/ExternalSort  ${inDataPath}.${method}CPP ${outDataPath} ${method} ${chunk_size}"
    if [ "$task_set" = true ] ; then
        SCRIPT="taskset -c 0 $SCRIPT"
    fi
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"CPP,CPP,"${task_set}","${chunk_size}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    