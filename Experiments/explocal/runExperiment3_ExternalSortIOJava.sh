#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4
task_set=$5
chunk_size=$6
log_file_name=$7

# clean OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
sleep 30

SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
               -DoutDataPath=${outDataPath}\
               -Dnrow=${nrow}\
               -DchunkSize=${chunk_size}\
               -Dmethod=${method}\
               -cp ./SerializationJava.jar at.tugraz.experiments.ExternalSortIO
        "
if [ "$task_set" = true ] ; then
    SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

start=$(date +%s%N) 
$SCRIPT
end=$(date +%s%N)
echo ${method}"Java,Java,"${task_set}",IO,"${chunk_size}","${nrow}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
   