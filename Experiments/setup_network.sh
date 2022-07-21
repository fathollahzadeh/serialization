#!/bin/bash

declare -a servers=("34.170.156.248" "35.232.213.107" "34.69.16.90" "34.69.16.90" "34.134.20.134" "34.134.20.134" "34.173.159.86") 

for server in "${servers[@]}"; do
    echo ">>>>>>>>>>>>>>>>>>>>> $server"
    src="/home/saeed/serialization"
    src_exp="$src/Experiments"
    src_data="$src/Experiments/data"
    ssh $server "mkdir -p $src"
    ssh $server "mkdir -p $src_exp"
    ssh $server "mkdir -p $src_data"

    scp -r ../Java $server:$src 
    scp -r *.sh $server:$src_exp
    scp -r expnetwork $server:$src_exp
    scp -r conf $server:$src_exp
done

