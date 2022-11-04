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
./cppbin/ComplexObjectL3
./cppbin/ComplexObjectL4

#ComplexObjectL1 avg serialization=1.0289  avg deserialize=2.9162   buffer size=1166

