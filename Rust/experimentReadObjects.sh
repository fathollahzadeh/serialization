#!/usr/bin/env bash

rm -rf loging.log

data_path=$1
random_list_path=$2

# for round:
for r in 1 2 3 4 5
do
    # for serialization types:
    for i in 1 2 3 4 5
    do
        #for number of objects:
        for n in  1000000 2000000 3000000 4000000 5000000
        do
      	 ./twitterSequentialRead.sh $i $n $r $data_path
          sleep 200
         ./twitterRandomRead.sh $i $n $r $data_path $random_list_path
          sleep 200
        done
    done
done
