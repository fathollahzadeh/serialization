#!/bin/bash

server_ip="35.239.123.205"

src="/mnt/disks/SSD/serialization"
src_exp="$src/Experiments"
src_data="$src/Experiments/data"
ssh $server_ip "mkdir -p $src"
ssh $server_ip "mkdir -p $src_exp"
ssh $server_ip "mkdir -p $src_data"

scp -r ../Java $server_ip:$src 
scp -r *.sh $server_ip:$src_exp
scp -r explocal $server_ip:$src_exp
scp -r conf $server_ip:$src_exp




