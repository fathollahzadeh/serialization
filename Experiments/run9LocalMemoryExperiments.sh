#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
inDataPathCPP="data/tweets.cbin"
inDataPathRust="data/tweets.rbin"
outDataPath="data/tmp/tweets"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") 
declare -a cpp_methods=("Handcoded") #("Handcoded" "inPlace" "Boost" "BoostBinary" "ProtoBuf" "Bson" "FlatBuf") 
declare -a rust_methods=("Json" "Bincode" "MessagePack" "Bson" "FlexBuf")  

max_nrow=10000000


rm -rf monitorResults
mkdir monitorResults

# for method in "${rust_methods[@]}"; do
#     #clean up
#     rm -rf data/tmp
#     mkdir -p data/tmp

#     ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $max_nrow Single false Experiment1_Write_times # Write (CPU+IO)
#     ./explocal/runExperiment4_MemoryRust.sh $method $outDataPath $max_nrow Single false Sequential Experiment4_Memory
# done

for method in "${cpp_methods[@]}"; do
    #clean up
    # rm -rf data/tmp
    # mkdir -p data/tmp
    
    # ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Single false Experiment1_Write_times # Write (CPU+IO)
    ./explocal/runExperiment4_MemoryCPP.sh $method $outDataPath $max_nrow Single false Sequential Experiment4_Memory
done

# for method in "${java_methods[@]}"; do
#     #clean up
#     rm -rf data/tmp
#     mkdir -p data/tmp
        
#     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Single false Experiment1_Write_times # Write (CPU+IO)
#     ./explocal/runExperiment4_MemoryJava.sh $method $outDataPath $max_nrow Single false Sequential Experiment4_Memory
# done