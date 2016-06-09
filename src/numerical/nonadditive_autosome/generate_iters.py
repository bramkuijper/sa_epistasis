#!/usr/bin/env python3

import numpy as np

r = [ 0.05, 0.2, 0.5 ]
hAf = [ 0.2, 0.8, 0.5 ]
ef1 = [ 0, -0.02, -0.05 ]
ef2 = [ 0, -0.02, -0.04, -0.05 ]
ef3 = [ 0, -0.02, -0.04, -0.05 ]
ef4 = [ 0, -0.02, -0.04, -0.05, -0.1 ]

exe = "./xsa_epistasis"

ctr = 1
for r_i in r:
    for hAf_i in hAf:
        hAm_i = hAf_i
        for ef1_i in ef1:
            for ef2_i in ef2:
                for ef3_i in ef3:
                    for ef4_i in ef4:
                        em1_i = ef1_i
                        em2_i = ef2_i
                        em3_i = ef3_i
                        em4_i = ef4_i

                        print("echo " + str(ctr))
                        ctr+=1
                        
                        print(exe + " " + str(r_i) + " " 
                                + str(hAf_i) + " " + str(hAf_i) + " " 
                                + str(ef1_i) + " " + str(ef2_i) + " " + str(ef3_i) + " " + str(ef4_i) + " "
                                + str(em1_i) + " " + str(em2_i) + " " + str(em3_i) + " " + str(em4_i)
                                )
