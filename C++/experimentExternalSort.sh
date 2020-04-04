#!/usr/bin/env bash

data_path=$1
number_of_splits=$2
# for round:
for r in 1 2 3 4 5
do
    # for serialization types:
    for i in  1 2 3 4 5
    do
        ./twitterExternalSort.sh $i $r $data_path $number_of_splits
        sleep 1
        # remove last experiment temp files
        rm -rf bin/tmp
    done
done