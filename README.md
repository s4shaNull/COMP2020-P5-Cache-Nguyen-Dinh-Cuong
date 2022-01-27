# COMP2020-P5-Cache-Nguyen-Dinh-Cuong
Team Members:
- Nguyen Dinh Cuong
- Nguyen Duy Anh Quan
- Nguyen Trong Nhan
- Tran Tuan Viet
### :chart_with_downwards_trend: Graph 1: Miss Rate vs. Cache Size
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151161395-18ff7e0e-5a57-4583-b1db-99ab5e8b46b3.png">
</p>

#### :question: Associated Questions
1. What is the smallest capacity that brings the miss rate to less than 10%? 
- Answer: 2^12 B or 4 KB
2. What is the smallest capacity that brings the miss rate to less than 5%?
- Answer: 2^14 B or 16 KB
3. Today's processors generally have 32KB to 128KB first-level data caches. By what ratio does increasing the cache size from 16KB to 32KB reduce the miss rate? (2.0 would be halving the miss rate; 1.0 would be no change in miss rate; less than 1.0 would be an increase in misses).
- Answer: 1.62/1.34 = 81/67 ~ 1.209
4. By what ratio does increasing the cache size from 32KB to 64KB reduce the miss rate?
- Answer: 1.34/1.17 = 134/117 ~ 1.145
5. When deciding on an ideal cache size, engineers typically look for the "knee" of the curve. (Links to an external site.) When considering various cache sizes, we want the point at which increasing to that size yields a great benefit, but increasing beyond that size yields far less benefit. What would you say is the ideal cache size for a direct mapped cache? 
- Answer: From the graph, we can see that the knee of the curve is at x = 14. Therefore, the ideal cache size for a direct mapped cache is 2^14 B or 16 KB
6. What is the smallest capacity that brings the miss rate of the 2-way set associative cache to less than 10%?
- Answer: 2^12 B or 4 KB
7. What is the smallest capacity that brings the miss rate of the 2-way set associative cache to less than 5%?
- Answer: 2^13 B or 8 KB
8. How large must the direct-mapped cache be before it equals or exceeds the performance of the 1 KB 2-way assoc?
- Answer: The miss rate of the 1 KB 2-way set associative cache is 11.18%. Thus, the direct-mapped cache must have the capacity of 2^11 B or 2 KB (the miss rate = 12.86%) before it equals or exceeds the performance of the 1 KB 2-way set associative cache

### :chart_with_downwards_trend: Graph 2: Bus Writes vs. Cache Size
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151166658-37b368eb-caa9-46c3-84cc-0aa6cf763aba.png">
</p>

#### :question: Associated Questions
9. At what cache size do the two write policies generate approximately the same amount of writes to the bus?
- Answer: From the graph, we can see that at x = 10, or cache size = 1 KB, the two write policies generate approximately the same amount of writes to the bus
10. Why does the difference between the two schemes diverge at small cache sizes?
- Answer:
11. Why does the difference between the two schemes diverge at large cache sizes?
- Answer:

### :chart_with_downwards_trend: Graph 3: Miss Rate vs. Block Size
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151237307-ac96285e-f94a-45f3-982a-79db45c43241.png">
</p>

#### :question: Associated Questions
12. Explain the observed miss rate associated with a small block size.
- Answer: As the block size decreases, the number of cold misses increases. Thus, we have a higher miss rate associated with a small block size
13. Explain the observed miss rate associated with a large block size.
- Answer: As the block size increases, the number of cold misses decreases. Thus, we have a lower miss rate associated with a large block size
14. What is the block size with the lowest miss rate?
- Answer: 512 B with 0.52% miss rate
18. Why does the miss rate get worse with more cores?
- Answer: In a multiprocessor system or a multicore processor, each cpu core/processor comes with its own cache memory. This results in more cold misses, thus, the miss rate get worse with more cores.
19. If the miss rate is so bad, why would one use the VI protocol over no protocol?
- Answer: Although the problem of cache coherency limits the performance of multicore systems, using the VI protocol is still better since the shift towards multicore will achieve continuing exponential performance gains. It's a trade off between the CPU time and the miss rate.

### :chart_with_downwards_trend: Graph 4: Total Memory Traffic vs Block Size
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151290015-ff03abfd-25e6-4248-bf1b-04afa1525b99.png">
</p>

#### :question: Associated Questions
15. What is the block size with the lowest total write-back traffic (transferred in + write-back transferred out)
- Answer: From the graph, we can see it's 2^2 or 4 B
16. What are the two sources of additional traffic as the block size grows? Explain why each grows.
- Answer: The first source of traffic is the data transfers to fill cache blocks (the number of misses multiplied by the block size). The other source of traffic is write traffics (for the write-back cache system, the traffic is the number of dirty evictions multiplied by the block size). Therefore, the two sources of traffic grows as the block size grows.
17. Given that current processors typically use, say, 64B blocks, which metric (miss rate or traffic) are today's caches designed to minimize?
- Answer: Average access time is the most important parameter for cache performance: tavg = thit + miss-rate * tmiss. This equation includes more than just the miss rate. A cache with a low miss rate but a large penalty per miss would perform worse than one with a greater miss rate but a significantly lower penalty per miss. It might also have a low miss rate but a long hit time (this is true for large fully associative caches, for instance). For this reason, multilevel of caching are employed. In a single cache, not all of the performance aspects can be maximized. It is challenging to build a cache that is both quick in the common case (a hit) and reduces the costly uncommon case by having a low miss rate when tmiss (memory delay) is specified. Two caches are used to fulfill these two design aims. Because the first level cache reduces hit time, it is generally small and has low associativity. The second level cache reduces the number of misses; it is typically huge, with large blocks and strong associativity. Since 64B is a typical block size for a Level 1 cache, and also as we can see from the graph, it is attempting to reduce the miss rate.

### :chart_with_downwards_trend: Graph 5: Replicate Graph #3 (Miss Rate vs Block Size for 1, 2, & 4 cores) but this time with MSI Protocol
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151241814-99a6246b-e530-4108-a801-c73059c91842.png">
</p>

#### :question: Associated Questions
20. Is there ever a scenario in which the VI protocol would be preferable to the MSI protocol? If so, provide that scenario. If not, explain why not.
- Answer:
21. For a 2 core trace, with a block size of 64B, what fraction of bus snoops by Core 0 are "hits" (i.e., the LD_MISS or ST_MISS on the bus is for a cache line that is currently valid in Core 0's cache.
- Answer: Fraction of bus snoops by Core 0 are "hits" = 50/365 = 10/73 ~ 0.137
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151306930-2f19e698-79c1-49ea-872f-4079d8eb5278.png">
</p>
22. For a 4 core trace, with a block size of 64B, what fraction of bus snoops by Core 0 are "hits"?

- Answer: Fraction of bus snoops by Core 0 are "hits" = 348/1110 = 58/185 ~ 0.314
<p align="center">
  <img src="https://user-images.githubusercontent.com/84661482/151307245-46376f37-5977-4f15-809c-9288dd875ab6.png">
</p>

23. What is one characteristic of the workload (visible in statistics in the output) that reconciles the high snoop hit rate and the low miss rates in Graph #5?
- Answer:



