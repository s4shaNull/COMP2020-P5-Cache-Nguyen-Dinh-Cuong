#!/usr/bin/python3                                                                                                                    

import time
import os

cap_lo = 8;
cap_high = 23; # up to but not including                                                                                              
bsize_lo = 6;
bsize_high = 7; # up to but not including                                                                                             
assoc = [1]

for i in range(cap_lo, cap_high):
    for j in assoc:
        for k in range(bsize_lo, bsize_high):
            os.system("./p5 -t route.1t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+"| grep 'capacity' >> ./GraphsAndLogFiles/Graph1/logdirect.txt")
            os.system("./p5 -t route.1t.long.txt -cache "+str(i)+" "+str(k)+" "+str(j)+"| grep 'miss_rate'| cut -d '.' -f 2- >> ./GraphsAndLogFiles/Graph1/logdirect.txt")

