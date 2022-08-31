#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4
task_set=$5
chunk_size=$6
log_file_name=$7

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
                   -DoutDataPath=${outDataPath}\
                   -Dnrow=${nrow}\
                   -DchunkSize=${chunk_size}\
                   -Dmethod=${method}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.ExternalSort
            "
    if [ "$task_set" = true ] ; then
        SCRIPT="taskset -c 0 $SCRIPT"
    fi
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"Java,Java,"${task_set}",Total,"${chunk_size}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    