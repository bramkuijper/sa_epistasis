#!/usr/bin/env python3

import os, re

# file with the mathematica expressions
filename_exp = "recursions.txt"

# C++ file
filename_c = "sa_epistasis.cpp"

# the necessary regexps
regexps = [(r"(x|y)\((\d+)\)","\\1\\2")]

f = open(filename_exp)
fl = f.read()
f.close()

for regexp_i in regexps:
    fl = re.sub(regexp_i[0],regexp_i[1],fl)


f = open(filename_c)
fl2 = f.read()
f.close()

fl2 = re.sub("ITERATIONS_HERE",fl,fl2)

f = open("sa_epistasis2.cpp","w")

f.write(fl2)

f.close()
