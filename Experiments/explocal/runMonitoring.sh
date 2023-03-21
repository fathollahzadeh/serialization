#!/bin/bash

log_file_name=$1

pkill -f monitorMemory.sh

./explocal/monitorMemory.sh $log_file_name &