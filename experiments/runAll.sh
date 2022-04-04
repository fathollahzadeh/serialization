#!/bin/bash

# clean original results
rm -rf results/*;
mkdir -p results;

# setup, run experiments, plots
./run1SetupDependencies.sh;
./run2DownloadData.sh;
./run3LocalExperiments.sh;
