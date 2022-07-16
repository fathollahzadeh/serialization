#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
randomDataPath="data/random_list_"
outDataPath="data/out/tweets"
#declare -a nrows=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000)

declare -a nrows=(100000 200000 300000)

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,seq_rand,nrow,time" >>results/Experiment1a_LoadToMemory_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment1_Write_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment2_Read_times.dat

for nrow in "${nrows[@]}"; do
    ./explocal/runExperiment1a_LoadToMemory.sh $inDataPathJava Single Sequential $nrow Experiment1a_LoadToMemory_times
    ./explocal/runExperiment1a_LoadToMemory.sh $inDataPathJava Parallel Sequential $nrow Experiment1a_LoadToMemory_times
    ./explocal/runExperiment1a_LoadToMemory.sh $inDataPathJava Single Random $nrow Experiment1a_LoadToMemory_times "$randomDataPath$nrow.dat"
    ./explocal/runExperiment1a_LoadToMemory.sh $inDataPathJava Parallel Random $nrow Experiment1a_LoadToMemory_times "$randomDataPath$nrow.dat"


    # # Seralization (just CPU time)
    # ##############################

    # ./explocal/runExperiment1b_Serialization.sh $inDataPathJava $nrow Single false Experiment1_Write_times
    # ./explocal/runExperiment1b_Serialization.sh $inDataPathJava $nrow Single true Experiment1_Write_times
    # ./explocal/runExperiment1b_Serialization.sh $inDataPathJava $nrow Parallel false Experiment1_Write_times


    # # Write (CPU+IO)
    # ###############
    # ./explocal/runExperiment1c_Write.sh $inDataPathJava $outDataPath $nrow Single false Experiment1_Write_times
    # ./explocal/runExperiment1c_Write.sh $inDataPathJava $outDataPath $nrow Single true Experiment1_Write_times
    # ./explocal/runExperiment1c_Write.sh $inDataPathJava $outDataPath $nrow Parallel false Experiment1_Write_times


    # # De-Seralization (just IO time)
    # ###############################

    # ./explocal/runExperiment2a_ReadIO.sh $inDataPathJava $nrow Single false Experiment2_Read_times
    # ./explocal/runExperiment2a_ReadIO.sh $inDataPathJava $nrow Single true Experiment2_Read_times
    # ./explocal/runExperiment2a_ReadIO.sh $inDataPathJava $nrow Parallel false Experiment2_Read_times


    # # Read (CPU+IO)
    # ./explocal/runExperiment2a_Read.sh $inDataPathJava $nrow Single false Experiment2_Read_times
    # ./explocal/runExperiment2a_Read.sh $inDataPathJava $nrow Single true Experiment2_Read_times
    # ./explocal/runExperiment2a_Read.sh $inDataPathJava $nrow Parallel false Experiment2_Read_times

done


