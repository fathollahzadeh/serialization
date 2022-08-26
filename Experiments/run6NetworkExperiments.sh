#!/bin/bash

# This script runs all network experiments on the cluster scale-up machines.
inDataPathMemoryJava="data/tweets.jbin"
inDataPathMemoryCPP="data/tweets.cbin"
inDataPathDisk="data/tmp/tweets"
outDataPath="data/tmp/tweets"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") 
declare -a cpp_methods=("inPlace") #("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf") 

nrow=100000

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "baseline,language,plan,machineip,time" >>results/Experiment4_ExternalSort_times.dat

# for method in "${java_methods[@]}"; do
#     #clean up
#     rm -rf data/tmp
#     mkdir -p data/tmp

#     # serialize data into disk
#     ./expnetwork/runExperiment4_WriteJava.sh $method $inDataPathMemoryJava $outDataPath $nrow 

#     # 1. Memory-to-Memory (m2m)
#     ./expnetwork/runExperiment4_ExternalSortJava.sh $method $inDataPathMemoryJava $outDataPath m2m Experiment4_ExternalSort_times

#     # 2. Memory-to-Disk
#     ./expnetwork/runExperiment4_ExternalSortJava.sh $method $inDataPathMemoryJava $outDataPath m2d Experiment4_ExternalSort_times

#     # 3. Disk-to-Memory (d2m)
#     ./expnetwork/runExperiment4_ExternalSortJava.sh $method $inDataPathDisk $outDataPath d2m Experiment4_ExternalSort_times

#     # 4. Disk-to-Disk (d2d)
#     ./expnetwork/runExperiment4_ExternalSortJava.sh $method $inDataPathDisk $outDataPath d2d Experiment4_ExternalSort_times
# done    


for method in "${cpp_methods[@]}"; do
    #clean up
    rm -rf data/tmp
    mkdir -p data/tmp

    # serialize data into disk
    ./expnetwork/runExperiment4_WriteCPP.sh $method $inDataPathMemoryCPP ${outDataPath}.${method}CPP $nrow 

    # 1. Memory-to-Memory (m2m)
    ./expnetwork/runExperiment4_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP m2m Experiment4_ExternalSort_times

    # # 2. Memory-to-Disk
    # ./expnetwork/runExperiment4_ExternalSortCPP.sh $method $inDataPathMemoryCPP $outDataPath m2d Experiment4_ExternalSort_times

    # # 3. Disk-to-Memory (d2m)
    # ./expnetwork/runExperiment4_ExternalSortCPP.sh $method $inDataPathDisk $outDataPath d2m Experiment4_ExternalSort_times

    # # 4. Disk-to-Disk (d2d)
    # ./expnetwork/runExperiment4_ExternalSortCPP.sh $method $inDataPathDisk $outDataPath d2d Experiment4_ExternalSort_times
done   
