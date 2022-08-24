#!/bin/bash

declare -a servers=("128.31.27.142" "128.31.27.79" "128.31.27.109" "128.31.27.75" "128.31.27.165" "128.31.27.130" "128.31.27.128") 

for server in "${servers[@]}"; do
    echo ">>>>>>>>>>>>>>>>>>>>> $server"
    server="ubuntu@$server"
    src="/home/ubuntu"
    # src_exp="$src/Experiments"
    # src_data="$src/Experiments/data"
    # ssh $server "mkdir -p $src"
    # ssh $server "mkdir -p $src_exp"
    # ssh $server "mkdir -p $src_data"

    # scp -r ../Java $server:$src 
    # scp -r *.sh $server:$src_exp
    # scp -r expnetwork $server:$src_exp
    # scp -r conf $server:$src_exp
    scp -r  run1SetupDependencies.sh $server:$src
done

