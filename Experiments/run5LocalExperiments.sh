#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
inDataPathCPP="data/tweets.cbin"
inDataPathRust="data/tweets.rbin"
randomDataPath="data/random_list_"
outDataPath="data/tmp/tweets"

declare -a java_methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") 
declare -a cpp_methods=("Handcoded" "inPlace" "Boost" "ProtoBuf" "Bson" "FlatBuf") 
declare -a rust_methods=("Json" "Bincode" "MessagePack" "Bson" "FlexBuf")  

max_nrow=10000000
declare -a nrows=(10000000 8000000 6000000 4000000 2000000)


# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "language,platform,taskset,nrow,time" >>results/Experiment1_LoadToMemory_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment1_Write_times.dat
echo "baseline,language,taskset,execution,platform,seq_rand,nrow,time" >>results/Experiment2_Read_times.dat

for rp in {1..5}; do

    for method in "${rust_methods[@]}"; do
        #clean up
        rm -rf data/tmp
        mkdir -p data/tmp

        # serialize/write data into disk
        ##############################
        # Seralization (just CPU time)
        ./explocal/runExperiment1b_SerializationRust.sh $method $inDataPathRust $max_nrow Single false Experiment1_Write_times
        ./explocal/runExperiment1b_SerializationRust.sh $method $inDataPathRust $max_nrow Single true Experiment1_Write_times
        ./explocal/runExperiment1b_SerializationRust.sh $method $inDataPathRust $max_nrow Parallel false Experiment1_Write_times

        # Write (CPU+IO)
        #############
        ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $max_nrow Single false Experiment1_Write_times
        ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $max_nrow Single true Experiment1_Write_times
        ./explocal/runExperiment1c_WriteRust.sh $method $inDataPathRust $outDataPath $max_nrow Parallel false Experiment1_Write_times

        # Load to memory
        ./explocal/runExperiment1a_LoadToMemoryRust.sh $inDataPathRust Single true $max_nrow Experiment1_LoadToMemory_times
        ./explocal/runExperiment1a_LoadToMemoryRust.sh $inDataPathRust Single false $max_nrow Experiment1_LoadToMemory_times
        ./explocal/runExperiment1a_LoadToMemoryRust.sh $inDataPathRust Parallel false $max_nrow Experiment1_LoadToMemory_times

        # De-Seralization (just IO time)
        ##############################
        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Single false Sequential Experiment2_Read_times
        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Single true Sequential Experiment2_Read_times
        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Parallel false Sequential Experiment2_Read_times

        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Single false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Single true Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
        ./explocal/runExperiment2a_ReadIORust.sh $method $outDataPath $max_nrow Parallel false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"

        for nrow in "${nrows[@]}"; do            
              # Read (CPU+IO)
             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
             ./explocal/runExperiment2a_ReadRust.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
         done
    done

    #for method in "${cpp_methods[@]}"; do
         #clean up
         #rm -rf data/tmp
         #mkdir -p data/tmp
      
        # serialize/write data into disk
        ###############################
        # Seralization (just CPU time)
      #   ./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Single false Experiment1_Write_times
      #   ./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Single true Experiment1_Write_times
      #   ./explocal/runExperiment1b_SerializationCPP.sh $method $inDataPathCPP $max_nrow Parallel false Experiment1_Write_times

        # Write (CPU+IO)
        ##############
        #./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Single false Experiment1_Write_times
      #   ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Single true Experiment1_Write_times
      #   ./explocal/runExperiment1c_WriteCPP.sh $method $inDataPathCPP $outDataPath $max_nrow Parallel false Experiment1_Write_times
    
      #   ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Single true $max_nrow Experiment1_LoadToMemory_times
      #   ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Single false $max_nrow Experiment1_LoadToMemory_times
      #   ./explocal/runExperiment1a_LoadToMemoryCPP.sh $inDataPathCPP Parallel false $max_nrow Experiment1_LoadToMemory_times

      #    #De-Seralization (just IO time)
      #    ##############################
      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Single false Sequential Experiment2_Read_times
      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Single true Sequential Experiment2_Read_times
      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Parallel false Sequential Experiment2_Read_times

      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Single false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Single true Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
      #    ./explocal/runExperiment2a_ReadIOCPP.sh $method $outDataPath $max_nrow Parallel false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"

      #    for nrow in "${nrows[@]}"; do    
      #        #Read (CPU+IO)
      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
      #       ./explocal/runExperiment2a_ReadCPP.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"

      #   done
   # done


    #for method in "${java_methods[@]}"; do
      #  # clean up
      #  rm -rf data/tmp
      #  mkdir -p data/tmp

        #serialize/write data into disk
        ###############################
        #Seralization (just CPU time)
        # ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Single false Experiment1_Write_times
        # ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Single true Experiment1_Write_times
        # ./explocal/runExperiment1b_SerializationJava.sh $method $inDataPathJava $max_nrow Parallel false Experiment1_Write_times

        # Write (CPU+IO)
        ###############
        # ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Single false Experiment1_Write_times
        # ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Single true Experiment1_Write_times
        # ./explocal/runExperiment1c_WriteJava.sh $method $inDataPathJava $outDataPath $max_nrow Parallel false Experiment1_Write_times

        # Load to Memory
        #./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single true $max_nrow Experiment1_LoadToMemory_times
        # ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Single false $max_nrow Experiment1_LoadToMemory_times
        # ./explocal/runExperiment1a_LoadToMemoryJava.sh $inDataPathJava Parallel false $max_nrow Experiment1_LoadToMemory_times

         # De-Seralization (just IO time)
         ###############################
        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Single false Sequential Experiment2_Read_times
        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Single true Sequential Experiment2_Read_times
        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Parallel false Sequential Experiment2_Read_times

        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Single false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Single true Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"
        # ./explocal/runExperiment2a_ReadIOJava.sh $method $outDataPath $max_nrow Parallel false Random Experiment2_Read_times "$randomDataPath$max_nrow.dat"


        # for nrow in "${nrows[@]}"; do                

        #     # Read (CPU+IO)
        #    ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single false Sequential Experiment2_Read_times
        #     ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single true Sequential Experiment2_Read_times
        #     ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Parallel false Sequential Experiment2_Read_times

        #     ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
        #     ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Single true Random Experiment2_Read_times "$randomDataPath$nrow.dat"
        #     ./explocal/runExperiment2a_ReadJava.sh $method $outDataPath $nrow Parallel false Random Experiment2_Read_times "$randomDataPath$nrow.dat"
        #  done        
    #done
done    