#!/bin/bash

# inDataPath=$1
# platform=$2
# task_set=$3
# nrow=$4
# log_file_name=$5

# # clean OS cache
# echo 3 > /proc/sys/vm/drop_caches && sync
# sleep 30

./cppbin/SimpleObject
./cppbin/ComplexObjectL1
./cppbin/ComplexObjectL2

