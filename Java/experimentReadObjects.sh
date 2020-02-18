#!/usr/bin/env bash

rm -rf loging.log
# for round:
for r in 1 #2 3 4 5
do
    # for serialization types:
    for i in 1 #2 3 4 5 6
    do
        #for number of objects:
        for n in  978 #1000000 2000000 3000000 4000000 5000000
        do
        ./twitterSequentialRead.sh $i $n $r
        #./twitterRandomRead.sh $i $n $r
        done
    done
done