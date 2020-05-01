#!/usr/bin/env bash

#number of reads
number_of_read_object=$2

./resultPath.sh $number_of_read_object $3

#serialization type
serialization_type=$1

#set data and out serialization files path
datapath="$4/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

echo "start to benchmark for << sequential read >>  with $number_of_read_object objects: serialization type="$serialization_type

#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

# start to monitor CPU and Memory
filenamevar1="$number_of_read_object"
filenamevar2="_$3"
filename="taskset_true_javaTwitterSequentialRead$filenamevar1$serialization_type$filenamevar2"
#pkill -f java
../monitor/run.sh $filename

time taskset -c 0  java -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx7g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.SequentialRead $datapath $serialization_type 0 $number_of_read_object $3 true

sleep 200

echo 3 > /proc/sys/vm/drop_caches && sync

# stop last monitoring and start new for tast set true
#pkill -f java
filename="taskset_false_javaTwitterSequentialRead$filenamevar1$serialization_type$filenamevar2"
../monitor/run.sh $filename

time java -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx7g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.SequentialRead $datapath $serialization_type 0 $number_of_read_object $3 false
