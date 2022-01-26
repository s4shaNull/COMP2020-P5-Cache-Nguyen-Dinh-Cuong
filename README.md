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
11. Why does the difference between the two schemes diverge at large cache sizes?

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

### :chart_with_downwards_trend: Graph 4: Total Memory Traffic vs Block Size





