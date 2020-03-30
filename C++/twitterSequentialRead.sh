#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""

#define a name for project target
project_target="TwitterSequentialRead"

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
#valgrind  -v --leak-check=yes ./bin/$project_target $datapath $serialization_type 0 $number_of_read_object $3

#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

#run the experiment
time ./bin/$project_target $datapath $serialization_type 0 $number_of_read_object $3
