#!/usr/bin/env bash

# for round:
for r in 1 #2 3 4 5
do
    # for serialization types:
    for i in 2 #1 2 3 4
    do
        ./twitterExternalSort.sh $i $r
    done
done