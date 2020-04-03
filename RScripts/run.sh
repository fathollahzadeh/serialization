#!/bin/bash

# CPU experiment read objects, sequential and random read
Rscript Experiment_ReadObjects_CPU.R

# IO experiment read objects, sequential and random read
Rscript Experiment_ReadObjects_IO.R

# experiment external sort
Rscript Experiment_ExternalSort.R

#data overview 
#Rscript Data_Overview.R


