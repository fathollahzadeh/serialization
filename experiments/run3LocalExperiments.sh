#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
export jCMD="java -Xms15g -Xmx15g"

# Experiment1: Serialization(Load Object to a List+ I/O Write + CPU Execution Time)
# 1. sub-exp: Load Object to a List
experiment1a="Experiment1a_times"
echo "language,dataset,time" >>results/$experiment1a.dat # write a header
./explocal/runExperiment1a_load_obj_Java.sh twitter.dat Twitter $experiment1a


