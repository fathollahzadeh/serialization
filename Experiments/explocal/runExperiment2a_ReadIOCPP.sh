#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
seq_rand=$6
log_file_name=$7
randomDataPath=$8

# clean OS cache
sync && echo 3 >/proc/sys/vm/drop_caches

start=$(date +%s%N) 
SCRIPT="./cppbin/DataReadIO${platform} ${inDataPath}.${method}CPP ${method} ${seq_rand} ${nrow} ${randomDataPath}"    
if [ "$task_set" = true ] ; then
    SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT
time $SCRIPT
end=$(date +%s%N)
echo ${method}"CPP,CPP,"${task_set}",IO,"${platform}","${seq_rand}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
