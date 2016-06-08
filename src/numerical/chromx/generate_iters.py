#!/usr/bin/env python3

import numpy as np

cf = list(np.arange(0,1,0.1))
cm = list(np.arange(0,1,0.1))
r = list(np.arange(0,0.5,0.1))
kdrive = list(np.arange(0.5,1.0,0.1))

exe = "./xdrive"

ctr = 1
for cf_i in cf:
    for cm_i in cm:
        for r_i in r:
            for kdrive_i in kdrive:
                print("echo " + str(ctr))
                ctr+=1

                print(exe + " " + str(cf_i) + " " + str(cm_i) + " " + str(kdrive_i) + " " + str(r_i))

