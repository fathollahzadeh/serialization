#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPath="data/tweets.bin"
outDataPath="data/out/tweets"
nrow=100000

# Load data into memory
# 1.a Java enviroments
#./explocal/runExperiment1a_LoadToMemory.sh $inDataPath $nrow Experiment1a_LoadToMemory_times


# Seralization (just CPU time)
#./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Single false Experiment1_Write_times
#./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Single true Experiment1_Write_times
./explocal/runExperiment1b_Serialization.sh $inDataPath $nrow Parallel false Experiment2_Write_times


# # Write (CPU+IO)
# ./explocal/runExperiment1c_Write.sh $inDataPath $outDataPath $nrow single false Experiment1_Write_times
# ./explocal/runExperiment1c_Write.sh $inDataPath $outDataPath $nrow single true Experiment1_Write_times
