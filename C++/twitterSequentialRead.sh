#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""

#number of reads
number_of_read_object=$2

./makeClean.sh $number_of_read_object $3
#define a name for project target
project_target="TwitterSequentialRead"

#serialization type
serialization_type=$1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto

#set data and out serialization files path
datapath="data/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

echo "start to benchmark for sequential $serialization_type read with $number_of_read_object objects:"
#valgrind  -v --leak-check=yes ./bin/$project_target $datapath $serialization_type 0 $number_of_read_object $3
time ./bin/$project_target $datapath $serialization_type 0 $number_of_read_object $3
