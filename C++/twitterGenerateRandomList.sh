#!/usr/bin/env bash
# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
#cmake .
#make clean
make -j4
mkdir -p "bin/benchmark"
mkdir -p "bin/benchmark/readobjects"

#define a name for project target
project_target="TwitterGenerateRandomList"

#define maximum value can be generate
maximum_value=6000000;

#for number of objects:
for n in 1000000 2000000 3000000 4000000 5000000
do
   outpath="bin/benchmark/readobjects/randomlist_$n.txt"
   ./bin/$project_target $n $maximum_value $outpath
done



