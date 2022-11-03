#!/bin/bash

# clean original results
rm -rf benchmark_results
mkdir -p benchmark_results

./run2SetupSerialization.sh
./run8Benchmark.sh