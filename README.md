## PixelSum
This repository contains an implementation to PixelSum algorithm. PixelSum is an algorithm that allow us to have O(1)
complexity for The sum and the average of the image pixels within a query window. \\

The main idea of the algorithm is to preprocess the image by building a data structure (Sum Area Table) that allow us to
have a constant time queries. More information can be found [here](https://en.wikipedia.org/wiki/Summed-area_table) and [here]
(https://www.geeksforgeeks.org/summed-area-table-submatrix-summation/). \\

---
### Build
``` make build ```
---
### Run test cases
``` cd build ```
``` ./pixelSum ```
---
### Add more test cases
The test cases are divided into 3 tests:
1- Test PixelSum functions. The cases can be found in ```tests/TestCases.cpp```. Please, add any new test case following the same format. \\
2- Test Swap points function. The cases can be found in ```tests/dataForTestSwapPoints.h```. Please, add any new test case following the same format. \\
3- Test borders clamping function. The cases can be found in ```tests/dataForTestSwapPoints.h```. Please, add any new test case following the same format. \\

---
### Memory check
The code should not produce any Memory leak according to Valgrind memory check. To run memory check, you need to build
the code in debug mode as follows:
``` make build-debug ```
``` cd build```
Then, you can pass the executable to valgrind as follows:
``` valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./pixelSum ```
The log is in valgrin-out.txt.

