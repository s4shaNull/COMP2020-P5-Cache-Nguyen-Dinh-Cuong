# COMP2020-P5-Cache-Nguyen-Dinh-Cuong
### :chart_with_downwards_trend: Graph 1: Miss Rate vs Cache Size
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
- Answer: 1.34 / 1.17 = 134/117 ~ 1.145
5. When deciding on an ideal cache size, engineers typically look for the "knee" of the curve. (Links to an external site.) When considering various cache sizes, we want the point at which increasing to that size yields a great benefit, but increasing beyond that size yields far less benefit. What would you say is the ideal cache size for a direct mapped cache? 
- Answer: From the graph, we can see that the knee of the curve is at x = 14. Therefore, the ideal cache size for a direct mapped cache is 2^14 B or 16 KB
6. What is the smallest capacity that brings the miss rate of the 2-way set associative cache to less than 10%?
- Answer: 2^12 B or 4 KB
7. What is the smallest capacity that brings the miss rate of the 2-way set associative cache to less than 5%?
- Answer: 2^13 B or 8 KB
8. How large must the direct-mapped cache be before it equals or exceeds the performance of the 1 KB 2-way assoc?
- Answer: The miss rate of the 1 KB 2-way set associative cache is 11.18%. Thus, the direct-mapped cache must have the capacity of 2 KB (the miss rate = 12.86%) before it equals or exceeds the performance of the 1 KB 2-way set associative cache.


