#!/usr/bin/env bash

./xsa_epistasis 0.05 0.2 0.2 0 0 &
./xsa_epistasis 0.05 0.8 0.8 0 0 &
./xsa_epistasis 0.05 0.5 0.5 0 0 &
./xsa_epistasis 0.05 0.2 0.2 -0.02 -0.02  &
./xsa_epistasis 0.05 0.8 0.8 -0.02 -0.02  &
./xsa_epistasis 0.05 0.5 0.5 -0.02 -0.02  &
