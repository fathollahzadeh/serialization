#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4
platform=$5
task_set=$6
log_file_name=$7

# clean OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
sleep 30

SCRIPT="./rustbin/DataWrite${platform} ${inDataPath} ${outDataPath}.${method}Rust ${nrow} ${method}"
if [ "$task_set" = true ] ; then
    SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

start=$(date +%s%N)
$SCRIPT
end=$(date +%s%N)
echo ${method}"Rust,Rust,"${task_set}",Total,"${platform}",Sequential,"${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat     