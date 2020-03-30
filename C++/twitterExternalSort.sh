#!/usr/bin/env bash

#define a name for project target
project_target="TwitterExternalSort"
mkdir -p "bin/tmp"

#serialization type
serialization_type=$1
number_of_files=$4

#set data and out serialization files path
datapath="$3/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

# check external sort log file
file_external_sort="bin/benchmark/externalsort/result_cpp_externalsort_$2.txt"
   if test ! -f "$file_external_sort"; then
       touch $file_external_sort
       echo "language#method#seq#datatype#iotime#totaltime" > $file_external_sort
   fi


#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

#run the experiment
./bin/$project_target $datapath $number_of_files $serialization_type $2