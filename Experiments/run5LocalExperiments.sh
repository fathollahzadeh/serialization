#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPath="data/tweets.bin"
outDataPath="data/out/tweets"
nrow=100000

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,time" >>results/Experiment1a_LoadToMemory_times.dat
./explocal/runExperiment1a_LoadToMemory.sh $inDataPath Single $nrow Experiment1a_LoadToMemory_times
./explocal/runExperiment1a_LoadToMemory.sh $inDataPath Parallel $nrow Experiment1a_LoadToMemory_times


# Seralization (just CPU time)
##############################
echo "baseline,language,taskset,execution,platform,time" >>results/Experiment1_Write_times.dat
./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Single false Experiment1_Write_times
./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Single true Experiment1_Write_times
./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Parallel false Experiment1_Write_times


# Write (CPU+IO)
###############
./explocal/runExperiment1c_Write.sh $inDataPath $outDataPath $nrow Single false Experiment1_Write_times
./explocal/runExperiment1c_Write.sh $inDataPath $outDataPath $nrow Single true Experiment1_Write_times
./explocal/runExperiment1c_Write.sh $inDataPath $outDataPath $nrow Parallel false Experiment1_Write_times


# De-Seralization (just IO time)
###############################
echo "baseline,language,taskset,execution,platform,time" >>results/Experiment2_Read_times.dat
./explocal/runExperiment2a_ReadIO.sh $inDataPath $nrow Single false Experiment2_Read_times
./explocal/runExperiment2a_ReadIO.sh $inDataPath $nrow Single true Experiment2_Read_times
./explocal/runExperiment2a_ReadIO.sh $inDataPath $nrow Parallel false Experiment2_Read_times


# Read (CPU+IO)
./explocal/runExperiment2a_Read.sh $inDataPath $nrow Single false Experiment2_Read_times
./explocal/runExperiment2a_Read.sh $inDataPath $nrow Single true Experiment2_Read_times
./explocal/runExperiment2a_Read.sh $inDataPath $nrow Parallel false Experiment2_Read_times



