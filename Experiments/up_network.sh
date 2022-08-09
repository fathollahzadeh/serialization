#!/bin/bash

declare -a servers=("128.31.27.142" "128.31.27.79" "128.31.27.109" "128.31.27.75" "128.31.27.165" "128.31.27.130" "128.31.27.128") 

src="/home/ubuntu/serialization"
src_exp="$src/Experiments"

for server in "${servers[@]}"; do
    server="ubuntu@$server"
    echo ">>>>>>>>>>>>>>>>>>>>> $server"
    scp -r ../Java/src/main/java/at/tugraz/experiments/DataReadNetwork.java $server:$src/Java/src/main/java/at/tugraz/experiments/DataReadNetwork.java

    #scp -r ../Java/src/main/java/at/tugraz/runtime/ObjectWriter.java $server:$src/Java/src/main/java/at/tugraz/runtime/ObjectWriter.java

    scp -r ../Java/src/main/java/at/tugraz/util/Const.java $server:$src/Java/src/main/java/at/tugraz/util/Const.java

    scp -r ../Java/src/main/java/at/tugraz/networkadapter/MachineInfo.java $server:$src/Java/src/main/java/at/tugraz/networkadapter/MachineInfo.java
    scp -r ../Java/src/main/java/at/tugraz/networkadapter/Network.java $server:$src/Java/src/main/java/at/tugraz/networkadapter/Network.java
    scp -r ../Java/src/main/java/at/tugraz/networkadapter/NodeSimpleInfo.java $server:$src/Java/src/main/java/at/tugraz/networkadapter/NodeSimpleInfo.java

     #scp -r ../Java $server:$src 
     #scp -r ../Java/src/main/java/at/tugraz/experiments/ $server:$src/Java/src/main/java/at/tugraz/experiments/
     #scp -r ../Java/src/main/java/at/tugraz/ $server:$src/Java/src/main/java/at/tugraz/
     scp -r conf/machines.inf $server:$src/Experiments/conf/machines.inf
     #scp -r conf/log4j.properties $server:$src/Experiments/conf/log4j.properties
     #scp -r runAll.sh $server:$src_exp
    #scp -r run4PrepareData.sh $server:$src_exp
done
