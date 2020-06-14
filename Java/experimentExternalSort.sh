#!/usr/bin/env bash

data_path=$1
number_of_splits=$2

# for round:
for r in 1 2 3 4 5
do
    # for serialization types:
    for i in 1 2 3 4 5 6 7
    do
        rm -rf bin/tmp
        if [ $i -eq 5 ]; then
            ./twitterExternalSortKryo.sh $i $r $data_path $number_of_splits
        else
           ./twitterExternalSort.sh $i $r $data_path $number_of_splits
        fi
        sleep 200
    done
done
