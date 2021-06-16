#!/usr/bin/env bash

mkdir -p "bin/tmp"

./resultPath.sh
serialization_type=$1
number_of_files=$4

#set data and out serialization files path
datapath="$3/serialization_$serialization_type.se"

echo "start to run the project"
echo "------------------------"

# check external sort log file
file_external_sort="bin/benchmark/externalsort/result_java_externalsort_$2.txt"
   if test ! -f "$file_external_sort"; then
       touch $file_external_sort
       echo "language#taskset#method#seq#datatype#iotime#totaltime" > $file_external_sort
   fi


#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync
echo "############ First Step for Kryo Task set TRUE " >> $file_external_sort
echo "=============================================== " >> $file_external_sort
time taskset -c 0 java -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms2g -Xmx6g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.ExternalSortKryo1 $datapath $number_of_files $serialization_type $2 true

echo "############ Second Step for Kryo Task set TRUE" >> $file_external_sort
echo "=============================================== " >> $file_external_sort
time taskset -c 0 java -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms2g -Xmx6g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.ExternalSortKryo2 $datapath $number_of_files $serialization_type $2 true
