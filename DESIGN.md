Craig Lindsay

Liam McDonald

We chose to implement a "sliding window" interpretation of window size, processing the trace of memory as it came in from valgrind. 

In order to do this we used a hash table and a linked list to identify which pages of memory where in use at any given time and which pages were leaving the working set. When a memory call was made the hash function would increment the appropriate box and the linked list would add it to the queue. Once the working set was full and a new call entered the function the oldest memory call would be removed from the queue and its box in the hash table would be decremented. 

Using this system, data was collected for use in histograms. 
