To implement multithreading, I had to consider the fact that I needed to multithread the entire for loop. 
So, this was separated into a separate function which was passed to the pthread-create function given by the pthread.h library. I ran into several issues while doing so. 

I ran into a problem with the original print statements of the for loop. When the print statements were in the for loop, they would result in weird images for multithreaded versions of the program. 
Part of the image would become more and more shuffled. I ended up moving the print statements back into the main function and the program worked fine. 
Partitioning the threads was difficult, often a case of trial and error. 
The main issue was with scaled_color, which would render the image pixel by pixel. I used an array based on width, hight, and color for the assignment and printing. 
I needed to increment to total number of threads for px to overcome race conditions as indicated by a segmentation fault (accessing not our memory). 

In the case of overall performance, mulithreading definitely increased the speed of the program. 
As shown by the time results given from make clean check, increasing threading exponentially reduced the time values for real. 
user and sys remained the same for all cases. Except, sys time appeared to be slightly decreasing up until 8-test.ppm. Such indicates the limits of multithreading.
Below are the times for command: make clean check

(1-test.ppm)
real   0m47.087s
user   0m47.077s
sys    0m0.003s

(2-test.ppm)
real   0m23.170s
user   0m45.780s
sys    0m0.002s

(4-test.ppm)
real   0m11.489s
user   0m44.985s
sys    0m0.001s

(8-test.ppm)
real   0m5.824s
user   0m45.015s
sys    0m0.003s

 
