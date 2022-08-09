#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
outDataPath="data/tmp/tweets"

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,taskset,seq_rand,nrow,time" >>results/Experiment5_LoadToMemory_times.dat

./expnetwork/runExperiment5b_ExternalSort.sh $inDataPathJava $outDataPath false Experiment5_LoadToMemory_times
