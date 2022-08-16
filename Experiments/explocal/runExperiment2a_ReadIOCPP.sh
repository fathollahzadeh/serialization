#!/bin/bash

inDataPath=$1
nrow=$2
platform=$3
task_set=$4
seq_rand=$5
log_file_name=$6
randomDataPath=$7

declare -a methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf")

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        start=$(date +%s%N)
        SCRIPT="./cppbin/DataReadIO${platform} ${inDataPath}.${method}CPP ${method} ${seq_rand} ${nrow} ${randomDataPath}"
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
        time $SCRIPT
        end=$(date +%s%N)
        echo ${method}"CPP,CPP,"${task_set}",IO,"${platform}","${seq_rand}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
    done
done    
