#!/bin/bash
file_name=$1


pkill -f mem.sh
#pkill -f cpu.sh

../monitor/mem.sh $file_name &
#../monitor/cpu.sh $experiment_name $file_name &
