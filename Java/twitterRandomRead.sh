#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""

#number of reads
number_of_read_object=$2

./makeClean.sh $number_of_read_object $3

#serialization type
serialization_type=$1

#set data and out serialization files path
datapath="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/jdata/serialization_$serialization_type.se"
random_list_path="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/randomlist/randomlist_$number_of_read_object.txt"

echo "start to run the project"
echo "------------------------"
echo "start to benchmark for sequential $serialization_type read with $number_of_read_object objects:"
time taskset -c 0 java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.RandomRead $datapath $serialization_type $number_of_read_object $3 $random_list_path
