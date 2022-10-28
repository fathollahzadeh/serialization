#!/bin/bash

# This script runs all network experiments on the cluster scale-up machines.
inDataPathMemoryJava="data/tweets.jbin"
inDataPathMemoryCPP="data/tweets.cbin"
inDataPathMemoryRust="data/tweets.rbin"
inDataPathDisk="data/tmp/tweets"
outDataPath="data/tmp/tweets"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers")
declare -a cpp_methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf") 
declare -a rust_methods=("Bincode") #("Json" "Bincode" "MessagePack" "Bson" "FlexBuf") 

nrow=50000

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "baseline,language,plan,machineip,time" >>results/Experiment4_ExternalSort_times.dat

# write all data into file
 #clean up
# rm -rf data/tmp
# mkdir -p data/tmp

# # for method in "${java_methods[@]}"; do    
# #     ./expnetwork/runExperiment4_WriteJava.sh $method $inDataPathMemoryJava ${outDataPath}.${method}Java $nrow 
# # done

# for method in "${cpp_methods[@]}"; do    
#     ./expnetwork/runExperiment4_WriteCPP.sh $method $inDataPathMemoryCPP ${outDataPath}.${method}CPP $nrow 
# done

# for method in "${rust_methods[@]}"; do
#     ./expnetwork/runExperiment4_WriteRust.sh $method $inDataPathMemoryRust ${outDataPath}.${method}Rust $nrow 
# done
method=Bincode
echo $1
./expnetwork/_runExperiment4_ExternalSortRust.sh $method ${outDataPath}.${method}Rust ${outDataPath}.${method}SortedRust d2d Experiment4_ExternalSort_times $1