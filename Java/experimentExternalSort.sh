#!/usr/bin/env bash

# for round:
for r in 1 #2 3 4 5
do
    # for serialization types:
    for i in 1 #1 2 3 4 5 6
    do
        rm -rf bin/tmp
        ./twitterExternalSort.sh $i $r
    done
done