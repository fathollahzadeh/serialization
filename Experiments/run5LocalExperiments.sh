#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
inDataPathCPP="data/tweets.cbin"
randomDataPath="data/random_list_"
outDataPath="data/tmp/tweets"
declare -a nrows=(1000000 2000000 3000000 4000000 5000000 6000000)

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,taskset,seq_rand,nrow,time" >>results/Experiment1_LoadToMemory_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment1_Write_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment2_Read_times.dat
echo "baseline,language,taskset,chunk_size,nrow,time" >>results/Experiment3_Read_times.dat

for nrow in "${nrows[@]}"; do
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single true Sequential $nrow Experiment1_LoadToMemory_times
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single false Sequential $nrow Experiment1_LoadToMemory_times
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Parallel false Sequential $nrow Experiment1_LoadToMemory_times
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single true Random $nrow Experiment1_LoadToMemory_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single false Random $nrow Experiment1_LoadToMemory_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Parallel false Random $nrow Experiment1_LoadToMemory_times "$randomDataPath$nrow.dat"


    # Seralization (just CPU time)
    ##############################
    ./explocal/runExperiment1b_SerializationJava.sh $inDataPathJava $nrow Single false Experiment1_Write_times
    ./explocal/runExperiment1b_SerializationJava.sh $inDataPathJava $nrow Single true Experiment1_Write_times
    ./explocal/runExperiment1b_SerializationJava.sh $inDataPathJava $nrow Parallel false Experiment1_Write_times

    #./explocal/runExperiment1b_SerializationCPP.sh $inDataPathCPP $nrow Single false Experiment1_Write_times
    #./explocal/runExperiment1b_SerializationCPP.sh $inDataPathCPP $nrow Single true Experiment1_Write_times
    #./explocal/runExperiment1b_SerializationCPP.sh $inDataPathCPP $nrow Parallel false Experiment1_Write_times


    # Write (CPU+IO)
    ###############
     ./explocal/runExperiment1c_WriteJava.sh $inDataPathJava $outDataPath $nrow Single false Experiment1_Write_times
     ./explocal/runExperiment1c_WriteJava.sh $inDataPathJava $outDataPath $nrow Single true Experiment1_Write_times
     ./explocal/runExperiment1c_WriteJava.sh $inDataPathJava $outDataPath $nrow Parallel false Experiment1_Write_times


    # De-Seralization (just IO time)
    ###############################
    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Single false Sequential Experiment2_Read_times
    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Single true Sequential Experiment2_Read_times
    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment2a_ReadIOJava.sh $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"


    # Read (CPU+IO)
    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Single false Sequential Experiment2_Read_times
    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Single true Sequential Experiment2_Read_times
    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment2a_ReadJava.sh $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"    
done

# External Sort
###############
nrow=10000000
./explocal/runExperiment3a_ExternalSortJava.sh $outDataPath $outDataPath $nrow false Experiment3_ExternalSort_times
./explocal/runExperiment3a_ExternalSortJava.sh $outDataPath $outDataPath $nrow true Experiment3_ExternalSort_times
