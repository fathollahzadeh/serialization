#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a temp path for save temporary sort
mkdir -p "bin/tmp"

#serialization type
serialization_type=$1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto
number_of_files=20

#set data and out serialization files path
datapath="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/jdata/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

# check external sort log file
file_external_sort="bin/benchmark/externalsort/result_java_externalsort_$2.txt"
   if test ! -f "$file_external_sort"; then
       touch $file_external_sort
       echo "language#method#seq#datatype#iotime#totaltime" > $file_external_sort
   fi

time taskset -c 0 java  -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.ExternalSort $datapath $number_of_files $serialization_type $2