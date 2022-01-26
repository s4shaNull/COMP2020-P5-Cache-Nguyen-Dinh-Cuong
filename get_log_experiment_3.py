#!/usr/bin/python3                                                                                                                    

import time
import os

cap_lo = 15;
cap_high = 16; # up to but not including                                                                                              
bsize_lo = 2;
bsize_high = 10; # up to but not including                                                                                             
assoc = [2]

for i in range(cap_lo, cap_high):
    for j in assoc:
        for k in range(bsize_lo, bsize_high):
            os.system("./p5 -t route.1t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+"| grep 'block_size' >> ./GraphsAndLogFiles/Graph3/log1core.txt")
            os.system("./p5 -t route.1t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+"| grep 'miss_rate'| cut -d '.' -f 2- >> ./GraphsAndLogFiles/Graph3/log1core.txt")
            os.system("./p5 -t route.2t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+" -n 2 -p vi | grep 'n_cpu\|n_misses' | cut -d '.' -f 2- >> ./GraphsAndLogFiles/Graph3/log2core.txt")
            os.system("./p5 -t route.4t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+" -n 4 -p vi| grep 'n_cpu\|n_misses'| cut -d '.' -f 2- >> ./GraphsAndLogFiles/Graph3/log4core.txt")

