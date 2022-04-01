### Essay Questions.

---

#### 1- Typical buffers in our use cases are extremely sparse matrices, i.e., the vast majority of the
pixels are zero. How would you exploit this to optimize the implementation? 

Having most values equal to zero, a sparse matrix representation should be used.
Sparse matrix is a data structure that allow us to convert dense matrix representation (with tons of zeros)
to a data structure that saves nonzero elements and their corresponding indices.
Sparse matrices are implemented using arrays or linked lists
(hash tables can be used as well for better memory complexity but more time complexity). List of lists (LIL)
and Compressed sparse raw are two common ways to represent a sparse matrix. Sparse matrices then
can sve memory. In addition, the time complexity for some operations for sparse matrices
can be less than dense ones. For example, matrix transpose for sparse matrix is O(N+M) where N is the
number of columns and M is the number of non zero elements while in dense matrix, it is O(N^2).
Addition is the same in both O(N) but keep in mind that the number of elements taken into 
calculate in sparse matrix (non zero ones) is less than the dense matrix.
---
#### 2- What changes to the code and the API need to be made if buffer dimensions can be >= 4096
x 4096? Also, what would happen if instead of 8 bits per pixel we have 16 bits per pixel?

Changing the dimensions of the buffer will lead to changing the expected max value for the sum. the max possible sum value is (2^bits_per_pixel x xWidth x yHeight).
This value should determine the data type that will be used to store the sum value saved in the data strucutre. Also, the return type of getPixelSum should be changed to match
the newly expected maximum value. The way to go here is to get the maximum possible sum value according to the equation mentioned above, then
determine the data type of the data strucutres and the return types of the APIs according to the new size. In my code, it should affect all the data types except the ones related to the buffer value (i.e. 
char related variables).
However, in the case of using 16 bits instead of 8, the ones related to the buffer (i.e. char related ones) should be changed as well. It means that the expected max sum (2^16 x xWidth x yHeight)
and the data type of the buffer will change from char to unsigned __int16.
---
#### 3- What would change if we needed to find the maximum value inside the search window
(instead of the sum or average)? You don't need to code this, but it would be interesting to know
how you would approach this problem in general, and what is your initial estimate of its
O-complexity. \

The brute force approach here is to have a linear search within the window with complexity O(N). However, with tons of
queries, it will become O(QxN) where Q is the number of Queries. One possible solution is to use sparse table approach or Range "Maximum" Query. For 2D (NxM) image, a precomputation step can be done
to make a data structure with O(MlogM x NlogN) complexity in time a space (however there are some papers suggensts some technique to get the complexity down to O(MN).
---
#### 4- How would multi-threading change your implementation? What kinds of performance benefits would you expect? 

multi threading can be used in building the sum table. If you look at the code in PixelSum.cpp, we can find that (frstRowCp) function at line 93 and the second loop of (colWiseAdd) function at line 101 can
be run in multithreading. Also, getting different queries from the table can be run in multi threads. We should expect higher performance
when the dimension and/or the number of queries are so high. However, for small dimensions and small number of queries, the overhead due to using threads 
can be more time consuming compared to the performance we get.
---
#### 5- Outline shortly how the class would be implemented on a GPU (choose any relevant technology, e.g. CUDA, OpenCL). No need to code anything, just a brief overview is sufficient. 

Using CUDA, Starting from the input buffer, A unified memory should be allocated to CUDA device, then the input buffer will be copied to GPU memory, then SUM AREA TABLE (integral image) can be
calculated. We should wait until the cores are synchronized. When we are done, The memory should be freed. The interface functions (i.e. query functions) will be tagged as kernel functions (__global__). During the querry, we can
determine the number of threads that can implement different queries by determining the grid size. During invoking these functions, an execution configuration should be used
to determine number of blocks and number of threads per block ( <num_block, num_threads>).

\__global__ \
interface functions

main(){

unified memory allocation \
copy data from the host to the device (GPU) \
kernel invoking \
wait for synchronization \
copy data from device to host \
free unified memory
}

