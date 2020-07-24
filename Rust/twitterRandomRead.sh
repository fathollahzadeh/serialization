#!/usr/bin/env bash

#number of reads
number_of_read_object=$2

#serialization type
serialization_type=$1

./resultPath.sh $number_of_read_object $3

#serialization type
serialization_type=$1

#set data and out serialization files path
datapath="$4/serialization_$serialization_type.se"
random_list_path="$5/randomlist_$number_of_read_object.txt"

echo "start to run the project"
echo "------------------------"
echo "start to run benchmark for << random read >> with $number_of_read_object objects: serialization type= "$serialization_type

#clear the OS cache
#echo 3 > /proc/sys/vm/drop_caches && sync

# stop monitoring
../monitor/stopmonitor.sh

# start to monitor CPU and Memory
filenamevar1="$number_of_read_object"
filenamevar2="_$3"
filename="taskset_true_rustTwitterRandomRead$filenamevar1$serialization_type$filenamevar2"

#start monitor
../monitor/run.sh $filename

time taskset -c 0 cargo run --release random_read $datapath $serialization_type $random_list_path $number_of_read_object $3 true

# stop monitoring
../monitor/stopmonitor.sh

sleep 1

#echo 3 > /proc/sys/vm/drop_caches && sync
filename="taskset_false_rustTwitterRandomRead$filenamevar1$serialization_type$filenamevar2"
../monitor/run.sh $filename

time cargo run --release random_read $datapath $serialization_type $random_list_path $number_of_read_object $3 false

# stop monitoring
../monitor/stopmonitor.sh
