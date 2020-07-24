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
file_external_sort="bin/benchmark/externalsort/result_rust_externalsort_$2.txt"
   if test ! -f "$file_external_sort"; then
       touch $file_external_sort
       echo "language#taskset#method#seq#datatype#iotime#totaltime" > $file_external_sort
   fi


#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

time taskset -c 0 cargo run --release external_sort $datapath $number_of_files $serialization_type $2 true


#clear the OS cache
echo 3 > /proc/sys/vm/drop_caches && sync

time cargo run --release external_sort $datapath $number_of_files $serialization_type $2 false

