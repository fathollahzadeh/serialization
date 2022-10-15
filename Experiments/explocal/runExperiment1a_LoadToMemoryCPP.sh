#!/bin/bash

inDataPath=$1
platform=$2
task_set=$3
nrow=$4
log_file_name=$5

# clean OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
sleep 100

SCRIPT="./cppbin/DataLoadToMemory${platform} ${inDataPath} ${nrow}"
if [ "$task_set" = true ] ; then
    SCRIPT="taskset -c 0 $SCRIPT"
fi            
echo $SCRIPT
start=$(date +%s%N)
$SCRIPT
end=$(date +%s%N)
echo "CPP,"${platform}","${task_set}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
