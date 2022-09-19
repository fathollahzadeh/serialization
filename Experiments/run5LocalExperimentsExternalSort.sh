#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
inDataPathCPP="data/tweets.cbin"
inDataPathRust="data/tweets.rbin"
outDataPath="data/tmp/tweets"
outExternalSort="data/tmp/externalsort"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") 
declare -a cpp_methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf") 
declare -a rust_methods=("Bincode") #("Json" "Bincode" "MessagePack" "Bson" "FlexBuf") 

externalsort_nrow=1000000
externalsort_hunk_size=100000


# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment3a_ExternalSort_Write_times.dat
echo "baseline,language,taskset,execution,chunk_size,nrow,time" >>results/Experiment3b_ExternalSort_times.dat

for rp in {1..1}; do
    # for method in "${java_methods[@]}"; do
    #     #clean up
    #     rm -rf data/tmp
    #     mkdir -p data/tmp
    #     mkdir -p $outExternalSort

    #     # External Sort
    #     ###############   
    #     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $externalsort_nrow Single false Experiment3a_ExternalSort_Write_times
        
    #     rm -rf $outExternalSort
    #     mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortJava.sh $method ${outDataPath}.${method}Java $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
    #     rm -rf $outExternalSort
    #     mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortIOJava.sh $method ${outDataPath}.${method}Java $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times 

    #     ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $externalsort_nrow Single true Experiment3a_ExternalSort_Write_times
       
    #     rm -rf $outExternalSort
    #     mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortJava.sh $method ${outDataPath}.${method}Java $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
    #     rm -rf $outExternalSort
    #     mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortIOJava.sh $method ${outDataPath}.${method}Java $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
    # done


    # for method in "${cpp_methods[@]}"; do
    #     #clean up
    #     rm -rf data/tmp
    #     mkdir -p data/tmp

    #     # External Sort
    #     ###############    
    #     ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $externalsort_nrow Single false Experiment3a_ExternalSort_Write_times

    #      rm -rf $outExternalSort
    #      mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortIOCPP.sh $method ${outDataPath}.${method}CPP $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
    #      rm -rf $outExternalSort
    #      mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times      
        

    #     ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $externalsort_nrow Single true Experiment3a_ExternalSort_Write_times
        
    #      rm -rf $outExternalSort
    #      mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortCPP.sh $method ${outDataPath}.${method}CPP $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
    #      rm -rf $outExternalSort
    #      mkdir -p $outExternalSort
    #     ./explocal/runExperiment3_ExternalSortIOCPP.sh $method ${outDataPath}.${method}CPP $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
    # done

     for method in "${rust_methods[@]}"; do
        #clean up
        rm -rf data/tmp
        mkdir -p data/tmp

        # External Sort
        ###############    
        ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $externalsort_nrow Single false Experiment3a_ExternalSort_Write_times

        rm -rf $outExternalSort
        mkdir -p $outExternalSort
        ./explocal/runExperiment3_ExternalSortIORust.sh $method ${outDataPath}.${method}Rust $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
        rm -rf $outExternalSort
        mkdir -p $outExternalSort
        ./explocal/runExperiment3_ExternalSortRust.sh $method ${outDataPath}.${method}Rust $outExternalSort $externalsort_nrow false $externalsort_hunk_size Experiment3b_ExternalSort_times      
        

        ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $externalsort_nrow Single true Experiment3a_ExternalSort_Write_times
        
        rm -rf $outExternalSort
        mkdir -p $outExternalSort
        ./explocal/runExperiment3_ExternalSortRust.sh $method ${outDataPath}.${method}Rust $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
        
        rm -rf $outExternalSort
         mkdir -p $outExternalSort
        ./explocal/runExperiment3_ExternalSortIORust.sh $method ${outDataPath}.${method}Rust $outExternalSort $externalsort_nrow true $externalsort_hunk_size Experiment3b_ExternalSort_times 
    done
done  