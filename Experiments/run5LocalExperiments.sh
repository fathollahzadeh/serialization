#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
inDataPathCPP="data/tweets.cbin"
randomDataPath="data/random_list_"
outDataPath="data/tmp/tweets"
mkdir -p data/tmp

# Java
declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") 
declare -a cpp_methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf")

#max_nrow=10000000
#declare -a nrows=(10000000 9000000 8000000 7000000 6000000 5000000 4000000 3000000 2000000 1000000)

max_nrow=1000000
declare -a nrows=(1000000)


# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,taskset,nrow,time" >>results/Experiment1_LoadToMemory_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment1_Write_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment2_Read_times.dat
echo "baseline,language,taskset,chunk_size,nrow,time" >>results/Experiment3_Read_times.dat


# for method in "${java_methods[@]}"; do
#     #clean up
#     rm -rf data/tmp
#     mkdir -p data/tmp

#     # serialize/write data into disk
#     ################################
#     # Seralization (just CPU time)
#     ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Single false Experiment1_Write_times
#     ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Single true Experiment1_Write_times
#     ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Parallel false Experiment1_Write_times

#     # Write (CPU+IO)
#     ###############
#     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Single false Experiment1_Write_times
#     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Single true Experiment1_Write_times
#     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Parallel false Experiment1_Write_times

#     for nrow in "${nrows[@]}"; do
#         ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single true $nrow Experiment1_LoadToMemory_times
#         ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single false $nrow Experiment1_LoadToMemory_times
#         ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Parallel false $nrow Experiment1_LoadToMemory_times

#         # De-Seralization (just IO time)
#         ###############################
#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
#         ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"

#         # Read (CPU+IO)
#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
#         ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"

#     done
# done


for method in "${cpp_methods[@]}"; do
    #clean up
    rm -rf data/tmp
    mkdir -p data/tmp

    # serialize/write data into disk
    ################################
    # Seralization (just CPU time)
    #./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Single false Experiment1_Write_times
    #./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Single true Experiment1_Write_times
    #./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Parallel false Experiment1_Write_times

    # # Write (CPU+IO)
    # ###############
    # ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Single false Experiment1_Write_times
    # ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Single true Experiment1_Write_times
     ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Parallel false Experiment1_Write_times

    # for nrow in "${nrows[@]}"; do
    #     ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Single true $nrow Experiment1_LoadToMemory_times
    #     ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Single false $nrow Experiment1_LoadToMemory_times
    #     ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Parallel false $nrow Experiment1_LoadToMemory_times

    #     # De-Seralization (just IO time)
    #     ###############################
    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    #     ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"

    #     # Read (CPU+IO)
    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    #     ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"

    # done
done



# External Sort
###############
# nrow=10000000
# ./explocal/runExperiment3a_ExternalSortJava.sh $outDataPath $outDataPath $nrow false Experiment3_ExternalSort_times
# ./explocal/runExperiment3a_ExternalSortJava.sh $outDataPath $outDataPath $nrow true Experiment3_ExternalSort_times
