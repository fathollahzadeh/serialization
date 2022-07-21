#!/bin/bash

declare -a servers=("34.170.156.248" "35.232.213.107" "34.69.16.90" "34.69.16.90" "34.134.20.134" "34.134.20.134" "34.173.159.86") 

src="/home/saeed/serialization"
src_exp="$src/Experiments"

for server in "${servers[@]}"; do
    echo ">>>>>>>>>>>>>>>>>>>>> $server"
    scp -r ../Java/src/main/java/at/tugraz/experiments/ $server:$src/Java/src/main/java/at/tugraz/experiments/
    scp -r run3DownloadData.sh $server:$src_exp
    scp -r run4PrepareData.sh $server:$src_exp
done
