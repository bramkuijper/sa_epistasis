#!/usr/bin/env bash

./generate_cpp.py

g++ -Wall -o xsa_epistasis sa_epistasis2.cpp -lm -lrt
