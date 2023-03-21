#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
seq_rand=$6
log_file_name=$7
randomDataPath=$8

SCRIPT="$jCMD  -DinDataPath=${inDataPath}.${method}Java\
               -Dnrow=${nrow}\
               -DseqRand=${seq_rand}\
               -DrandomDataPath=${randomDataPath}\
               -Dmethod=${method}\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataRead${platform}
        "
if [ "$task_set" = true ] ; then
    SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

rm -rf "monitorResults/$log_file_name_$method_times" #clean-up

./stopMonitoring.sh
./runMonitoring.sh "monitorResults/$log_file_name_$method_times"
$SCRIPT
./stopMonitoring.sh