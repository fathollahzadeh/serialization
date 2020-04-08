#!/usr/bin/env bash

data_path=$1
number_of_splits=$2

# for round:
for r in 1 #2 3 4 5
do
    # for serialization types:
    for i in 5 #1 2 3 4 5 6
    do
        rm -rf bin/tmp
        ./twitterExternalSort.sh $i $r $data_path $number_of_splits
        sleep 200
    done
done