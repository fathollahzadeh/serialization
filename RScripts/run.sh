#!/bin/bash


#=====================================
## CPU benchs
#Rscript Experiment_Seq_Read_CPU_Plot.R
#Rscript Experiment_Rand_Read_CPU_Plot.R

## CPU and IO Zoom
#Rscript Experiment_Seq_Read_CPU_IO_Bar.R
#Rscript Experiment_Rand_Read_CPU_IO_Bar.R

## CPU and IO serialization
#Rscript Experiment_SerializeObjects_Bar.R

## Memory 
#Rscript Experiment_ReadObjects_Memory.R 

# CPU experiment read objects, sequential and random read
#Rscript Experiment_ReadObjects.R


# serialization Bar graph
#Rscript Experiment_SerializeObjects_Bar.R

#Rscript Experiment_ReadObjects_Memory.R

# experiment external sort
Rscript Experiment_External_Sort_CPU_IO_Bar_60M.R

Rscript Experiment_External_Sort_CPU_IO_Bar_10M.R

#data overview 
#Rscript Data_Overview.R


# Sequential and Random read objects for Bar graph
#Rscript Experiment_ReadObjects_Sequential_Bar_TaskSet.R

#Rscript Experiment_ReadObjects_Random_Bar_TaskSet.R

#Rscript Experiment_ReadObjects_Sequential_RAM.R

#Rscript test.R






