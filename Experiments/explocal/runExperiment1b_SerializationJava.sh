#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
log_file_name=$6

# clean OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
sleep 30

SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
               -Dnrow=${nrow}\
               -Dmethod=${method}\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataSerialization${platform}
        "    
if [ "$task_set" = true ] ; then
      SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

start=$(date +%s%N)
$SCRIPT
end=$(date +%s%N)
echo ${method}"Java,Java,"${task_set}",CPU,"${platform}",Sequential,"${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat