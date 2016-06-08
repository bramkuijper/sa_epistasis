#!/usr/bin/env bash

./generate_cpp.py

un=`uname`

flags=''

if [ "$un" != 'Darwin' ]
    then flags="-lrt"
fi

g++ -Wall -o xsa_epistasis sa_epistasis2.cpp -lm $flags
