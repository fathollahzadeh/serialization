#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a name for project target
project_target="TwitterExternalSort"
mkdir -p "bin/tmp"

#serialization type
serialization_type=$1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto
number_of_files=20

#set data and out serialization files path
datapath="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

# check external sort log file
file_external_sort="bin/benchmark/externalsort/result_cpp_externalsort_$2.txt"
   if test ! -f "$file_external_sort"; then
       touch $file_external_sort
       echo "language#method#seq#datatype#iotime#totaltime" > $file_external_sort
   fi


./bin/$project_target $datapath $number_of_files $serialization_type $2