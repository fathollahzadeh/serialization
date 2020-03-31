#!/usr/bin/env bash
mkdir -p "bin/benchmark"
mkdir -p "bin/benchmark/externalsort"
mkdir -p "bin/benchmark/readobjects"


# check read objects log file
if [ ! -z "$2" ]; then
    file_read_objects="bin/benchmark/readobjects/result_cpp_readobjects_$1_$2.txt"
    if test ! -f "$file_read_objects"; then
        touch $file_read_objects
        echo "language#method#seq#datatype#iotime#totaltime" > $file_read_objects
    fi
fi