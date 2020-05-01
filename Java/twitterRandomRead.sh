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
echo 3 > /proc/sys/vm/drop_caches && sync

# stop monitoring
../monitor/stopmonitor.sh

# start to monitor CPU and Memory
filenamevar1="$number_of_read_object"
filenamevar2="_$3"
filename="taskset_true_javaTwitterRandomRead$filenamevar1$serialization_type$filenamevar2"

#start monitor
../monitor/run.sh $filename

time taskset -c 0 java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx8g -cp ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.RandomRead $datapath $serialization_type $number_of_read_object $3 $random_list_path true

# stop monitoring
../monitor/stopmonitor.sh

sleep 200

echo 3 > /proc/sys/vm/drop_caches && sync
filename="taskset_false_javaTwitterRandomRead$filenamevar1$serialization_type$filenamevar2"
../monitor/run.sh $filename

time java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx8g -cp ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.RandomRead $datapath $serialization_type $number_of_read_object $3 $random_list_path false

# stop monitoring
../monitor/stopmonitor.sh
