#!/usr/bin/env python3

import pandas as pd

the_data = pd.read_csv("all_output.csv",sep=";")

the_data_relevant = the_data[((the_data['faf'] > 0.001) & (the_data['faf'] < 0.999)) & ((the_data['fxd'] > 0.001) & (the_data['fxd'] < 0.999))]

the_data_relevant.to_csv("output_relevant.csv",sep=";")
