#!/usr/bin/env bash

#define a name for project target
project_target="TwitterGenerateRandomList"

#define maximum value can be generate
maximum_value=$1;
number_of_random_data=$2
mkdir -p "$3"
outpath="$3/randomlist_$number_of_random_data.txt"
./bin/$project_target $2 $maximum_value $outpath



