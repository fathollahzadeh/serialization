#!/bin/bash

method=$1
inDataPath=$2
nrow=$3
platform=$4
task_set=$5
seq_rand=$6
log_file_name=$7
randomDataPath=$8

SCRIPT="./cppbin/DataRead${platform} ${inDataPath}.${method}CPP ${method} ${seq_rand} ${nrow} ${randomDataPath}"
if [ "$task_set" = true ] ; then
     SCRIPT="taskset -c 0 $SCRIPT"
fi
echo $SCRIPT

rm -rf "monitorResults/"${log_file_name}"_"${method}"CPP_times.csv" #clean-up

./explocal/stopMonitoring.sh
./explocal/runMonitoring.sh "monitorResults/"${log_file_name}"_"${method}"CPP_times.csv"
$SCRIPT
./explocal/stopMonitoring.sh
