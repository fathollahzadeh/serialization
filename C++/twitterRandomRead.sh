#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
#number of reads
number_of_read_object=$2

./resultPath.sh $number_of_read_object $3

#define a name for project target
project_target="TwitterRandomRead"

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
# start to monitor CPU and Memory
filenamevar1="$number_of_read_object"
filenamevar2="_$3"
filename="taskset_false_cpp$project_target$filenamevar1$serialization_type$filenamevar2"
pkill -f $project_target
../monitor/run.sh $filename

# run the project without task set
time ./bin/$project_target $datapath $serialization_type $number_of_read_object $3 $random_list_path 0

sleep 200

#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

# stop last monitoring and start new for tast set true
pkill -f $project_target
filename="taskset_true_cpp$project_target$filenamevar1$serialization_type$filenamevar2"
../monitor/run.sh $filename

# runn the project with task set
time taskset -c 0 ./bin/$project_target $datapath $serialization_type $number_of_read_object $3 $random_list_path 1

# stop monitoring
pkill -f $project_target

