#!/bin/bash

# clean original plots
rm -rf plots/*;

cd explocal/V2-sigmod
make clean
make
cp -r plots/*.pdf ../../../V3-sigmod/plots/
