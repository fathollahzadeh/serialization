#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
log_file_name=$6

# clean OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
sleep 3


SCRIPT="./cppbin/DataSerialization${platform} ${inDataPath} ${method} ${nrow}"    
if [ "$task_set" = true ] ; then
     SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

start=$(date +%s%N)
$SCRIPT
end=$(date +%s%N)
echo ${method}"CPP,CPP,"${task_set}",CPU,"${platform}",Sequential,"${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat


