#!/bin/bash

inDataPath=$1
nrow=$2
platform=$3
task_set=$4
log_file_name=$5

declare -a methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf")

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        start=$(date +%s%N)
        SCRIPT="./cppbin/DataSerialization${platform} ${inDataPath} ${method} ${nrow}"
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
       time $SCRIPT
        end=$(date +%s%N)
        echo ${method}"CPP,CPP,"${task_set}",CPU,"${platform}",Sequential,"${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
    done
done  


