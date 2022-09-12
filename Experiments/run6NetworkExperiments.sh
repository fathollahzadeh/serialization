#!/bin/bash

# This script runs all network experiments on the cluster scale-up machines.
inDataPathMemoryJava="data/tweets.jbin"
inDataPathMemoryCPP="data/tweets.cbin"
inDataPathDisk="data/tmp/tweets"
outDataPath="data/tmp/tweets"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers")
declare -a cpp_methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf") 

nrow=500000

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "baseline,language,plan,machineip,time" >>results/Experiment4_ExternalSort_times.dat

for method in "${java_methods[@]}"; do
    #clean up
    rm -rf data/tmp
    mkdir -p data/tmp

    # serialize data into disk
    ./expnetwork/runExperiment4_WriteJava.sh $method $inDataPathMemoryJava ${outDataPath}.${method}Java $nrow 

    # 1. Memory-to-Memory (m2m)
    ./expnetwork/runExperiment4_ExternalSortJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava m2m Experiment4_ExternalSort_times

    # 2. Memory-to-Disk (m2d)
    #./expnetwork/runExperiment4_ExternalSortJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava m2d Experiment4_ExternalSort_times

    # 3. Disk-to-Memory (d2m)
    #./expnetwork/runExperiment4_ExternalSortJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava d2m Experiment4_ExternalSort_times

    # 4. Disk-to-Disk (d2d)
    ./expnetwork/runExperiment4_ExternalSortJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava d2d Experiment4_ExternalSort_times

    # 5. IO (m2m)
    #./expnetwork/runExperiment4_ExternalSortNetworkIOJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava m2m Experiment4_ExternalSort_times

    # 6. IO (m2d)
    #./expnetwork/runExperiment4_ExternalSortNetworkIOJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava m2d Experiment4_ExternalSort_times

    # 7. IO (d2m)
    #./expnetwork/runExperiment4_ExternalSortNetworkIOJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava d2m Experiment4_ExternalSort_times

    # 8. IO (d2d)
    rm -rf ${outDataPath}.${method}SortedJava
    ./expnetwork/runExperiment4_ExternalSortNetworkIOJava.sh $method ${outDataPath}.${method}Java ${outDataPath}.${method}SortedJava d2d Experiment4_ExternalSort_times
done    


# for method in "${cpp_methods[@]}"; do
#     #clean up
#     rm -rf data/tmp
#     mkdir -p data/tmp

#     # serialize data into disk
#     ./expnetwork/runExperiment4_WriteCPP.sh $method $inDataPathMemoryCPP ${outDataPath}.${method}CPP $nrow 

#     # 1. Memory-to-Memory (m2m)
#     #./expnetwork/runExperiment4_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP m2m Experiment4_ExternalSort_times

#     # 2. Memory-to-Disk (m2d)
#     #./expnetwork/runExperiment4_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP m2d Experiment4_ExternalSort_times

#     # 3. Disk-to-Memory (d2m)
#     #./expnetwork/runExperiment4_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP d2m Experiment4_ExternalSort_times

#     # 4. Disk-to-Disk (d2d)
#     ./expnetwork/runExperiment4_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP d2d Experiment4_ExternalSort_times

#     # 5. IO (m2m)
#     #./expnetwork/runExperiment4_ExternalSortNetworkIOCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP m2m Experiment4_ExternalSort_times

#     # 6. IO (m2d)
#     #./expnetwork/runExperiment4_ExternalSortNetworkIOCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP m2d Experiment4_ExternalSort_times

#     # 7. IO (d2m)
#     #./expnetwork/runExperiment4_ExternalSortNetworkIOCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP d2m Experiment4_ExternalSort_times

#     # 8. IO (d2d)
#     rm -rf ${outDataPath}.${method}SortedCPP
#     ./expnetwork/runExperiment4_ExternalSortNetworkIOCPP.sh $method ${outDataPath}.${method}CPP ${outDataPath}.${method}SortedCPP d2d Experiment4_ExternalSort_times
# done   