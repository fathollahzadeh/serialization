#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
#number of reads
number_of_read_object=$2

./makeClean.sh $number_of_read_object $3

#define a name for project target
project_target="TwitterRandomRead"

#serialization type
serialization_type=$1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto

#set data and out serialization files path
datapath="data/serialization_$serialization_type.se"
random_list_path="bin/benchmark/readobjects/randomlist_$number_of_read_object.txt"

echo "start to run the project"
echo "------------------------"


echo "start to run benchmark for random read with $number_of_read_object objects:"
./bin/$project_target $datapath $serialization_type $number_of_read_object $3 $random_list_path
