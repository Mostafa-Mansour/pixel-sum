//
// Created by Mostafa Mansour on 3/28/22.
//

#include "TestCases.h"
#include "UnitTest.h"
#include "../PixelSum.h"
#include "dataForTestSwapPoints.h"
#include "dataForTestClampBorderPoints.h"
#include <iostream>

#define MAX_WIDTH 4096L
#define MAX_HEIGHT 4096L
#define MAX_VALUE 255
#define MAX_SIZE MAX_WIDTH*MAX_HEIGHT






TestCases::TestCases():testSwapPoints(pointsBeforeSwap, expectedPointsAfterSwap, testCasesNames),
testClampBorderPoints(borderPointsBeforeClamping, expectedBorderPointsAfterClamping, testCasesNamesForClamping)
{
    // Prepare variables
    std::string name;
    int xWidth, yHeight;
    std::vector<unsigned char> buffer;
    int x0, y0, x1, y1;
    unsigned int pixelSum;
    double pixelAvg;
    int nonZeroCount;
    double nonZeroAverage;


    // CASE 1
    name = "Case 1: PixelSum data structure and operations simple check";
    xWidth = 5;
    yHeight = 5;
    buffer =
            {
                    1, 2, 3, 4, 5,
                    0, 1, 2, 3, 4,
                    1, 1, 1, 1, 1,
                    2, 2, 2, 2, 2,
                    3, 3, 3, 3, 3
            };
    x0 = 1, y0 = 1;
    x1 = 3, y1 = 2;
    // Expected results
    pixelSum = 9;
    pixelAvg = 1.5;
    nonZeroCount = 6;
    nonZeroAverage = 1.5;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 2
    name = "Case 2: One pixel buffer";

    xWidth = 1;
    yHeight = 1;
    buffer = {1};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 0;
    // Expected results
    pixelSum = 1;
    pixelAvg = 1;
    nonZeroCount = 1;
    nonZeroAverage = 1;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 3
    name = "Case 3: One pixel buffer (value 0)";

    xWidth = 1;
    yHeight = 1;
    buffer = {0};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 0;
    // Expected results
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 4
    name = "Case 4: One-dimentional buffer (row)";

    xWidth = 4;
    yHeight = 1;
    buffer = {0, 1, 2, 3};
    x0 = 0, y0 = 0;
    x1 = 2, y1 = 0;
    // Expected results
    pixelSum = 3;
    pixelAvg = 1;
    nonZeroCount = 2;
    nonZeroAverage = 1.5;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 5
    name = "Case 5: One-dimentional buffer (row with zeros)";

    xWidth = 4;
    yHeight = 1;
    buffer = {0, 1, 0, 1};
    x0 = 0, y0 = 0;
    x1 = 2, y1 = 0;
    // Expected results
    pixelSum = 1;
    pixelAvg = 0.333;
    nonZeroCount = 1;
    nonZeroAverage = 1;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 6
    name = "Case 6: One-dimentional buffer (column)";

    xWidth = 1;
    yHeight = 4;
    buffer = {0,
              1,
              2,
              3};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 2;
    // Expected results
    pixelSum = 3;
    pixelAvg = 1;
    nonZeroCount = 2;
    nonZeroAverage = 1.5;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 7
    name = "Case 7: Rectangular buffer";

    xWidth = 4;
    yHeight = 2;
    buffer = {0, 255, 255, 128,
              128, 255, 128, 0};
    x0 = 2, y0 = 0;
    x1 = 3, y1 = 1;
    // Expected results
    pixelSum = 511;
    pixelAvg = 127.75;
    nonZeroCount = 3;
    nonZeroAverage = 170.333;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 8
    name = "Case 8: Rectangular buffer";

    xWidth = 2;
    yHeight = 4;
    buffer = {1, 128,
              128, 100,
              0, 0,
              255, 10};
    x0 = 0, y0 = 3;
    x1 = 1, y1 = 1;
    // Expected results
    pixelSum = 493;
    pixelAvg = 82.166;
    nonZeroCount = 4;
    nonZeroAverage = 123.25;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));


    // CASE 9
    name = "case 9: Search window extends outside the buffer (bottom right)";

    xWidth = 5;
    yHeight = 5;
    buffer =
            {
                    1, 2, 3, 4, 5,
                    0, 1, 2, 3, 4,
                    1, 1, 1, 1, 1,
                    2, 2, 2, 2, 2,
                    3, 3, 3, 3, 3
            };
    x0 = 4, y0 = 4;
    x1 = 5, y1 = 5;
    // Expected results
    pixelSum = 3;
    pixelAvg = 0.75;
    nonZeroCount = 1;
    nonZeroAverage = 3;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 10
    name = "Case 10: Search window extends outside the buffer (bottom left)";

    xWidth = 5;
    yHeight = 5;
    buffer =
            {
                    1, 2, 3, 4, 5,
                    0, 1, 2, 3, 4,
                    1, 1, 1, 1, 1,
                    2, 2, 2, 2, 2,
                    3, 3, 3, 3, 3
            };
    x0 = -1, y0 = 5;
    x1 = 1, y1 = 2;
    // Expected results
    pixelSum = 12;
    pixelAvg = 1;
    nonZeroCount = 6;
    nonZeroAverage = 2;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 11
    name = "case 11: Search window extends completely outside the buffer";

    xWidth = 2;
    yHeight = 2;
    buffer =
            {
                    1, 2,
                    3, 4
            };
    x0 = 10, y0 = 10;
    x1 = 20, y1 = 20;
    // Expected results
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    // CASE 12
    name = "Case 12: Search window extends outside the buffer";

    xWidth = 2;
    yHeight = 2;
    buffer =
            {
                    1, 1,
                    1, 1
            };
    x0 = 1, y0 = 1;
    x1 = 3, y1 = 3;
    // Expected results
    pixelSum = 1;
    pixelAvg = 0.111;
    nonZeroCount = 1;
    nonZeroAverage = 1;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 13
    name = "Case 13: Search window extends outside the buffer";

    xWidth = 2;
    yHeight = 2;
    buffer =
            {
                    1, 1,
                    1, 1
            };
    x0 = 0, y0 = 0;
    x1 = 3, y1 = 3;
    // Expected results
    pixelSum = 4;
    pixelAvg = 0.25;
    nonZeroCount = 4;
    nonZeroAverage = 1;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 14
    name = "case 14: Max buffer size (4096x4096) with max pixel value (255)";

    xWidth = MAX_WIDTH;
    yHeight = MAX_HEIGHT;
    std::vector<unsigned char> maxBuffer(MAX_SIZE, MAX_VALUE);
    x0 = 0, y0 = 0;
    x1 = MAX_WIDTH - 1 , y1 = MAX_HEIGHT - 1;
    // Expected results
    pixelSum = (unsigned int) (MAX_WIDTH * MAX_HEIGHT * MAX_VALUE);
    pixelAvg = MAX_VALUE;
    nonZeroCount = MAX_WIDTH * MAX_HEIGHT;
    nonZeroAverage = MAX_VALUE;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              maxBuffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));


    // CASE 15

    name = "case 15: Max buffer size (4096x4096) with min pixel value (0)";

    xWidth = MAX_WIDTH;
    yHeight = MAX_HEIGHT;
    std::vector<unsigned char> minBuffer(MAX_SIZE, 0);
    x0 = 0, y0 = 0;
    x1 = MAX_WIDTH - 1 , y1 = MAX_HEIGHT - 1;
    // Expected results
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              minBuffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // CASE 16
    name = "Case 16: Check PixelSum copy constructor";

    xWidth = 3;
    yHeight = 3;
    buffer =
            {
                    1, 1, 1,
                    1, 1, 1,
                    1, 1, 1
            };
    x0 = 0, y0 = 0;
    x1 = 1, y1 = 1;

    unsigned char* buff = new unsigned char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), buff);

    // create first PixelSum object
    PixelSum pixelSum1(buff, xWidth, yHeight);
    delete[] buff;

    // check copy (create second PixelSum object)
    PixelSum pixelSumCopy(pixelSum1);
    // Expected results
    pixelSum = pixelSumCopy.getPixelSum(x0, y0, x1, y1); // 4
    pixelAvg = pixelSumCopy.getPixelAverage(x0, y0, x1, y1); // 1;
    nonZeroCount = pixelSumCopy.getNonZeroCount(x0, y0, x1, y1); // 4;
    nonZeroAverage = pixelSumCopy.getNonZeroAverage(x0, y0, x1, y1); // 1;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));


    // CASE 17
    name = "Case 17: Check PixelSum assign operator";

    xWidth = 2;
    yHeight = 2;
    buffer=
            {
                    10, 10,
                    10, 10
            };
    x0 = 0, y0 = 0;
    x1 = 1, y1 = 1;

    buff = new unsigned char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), buff);

    // create first PixelSum object
    PixelSum pixelSum2(buff, xWidth, yHeight);
    delete[] buff;

    // check assign (create second PixelSum object)
    PixelSum pixelSumAssign(pixelSum1);
    pixelSumAssign = pixelSum2;
    // Expected results
    pixelSum = pixelSumAssign.getPixelSum(x0, y0, x1, y1); // 40
    pixelAvg = pixelSumAssign.getPixelAverage(x0, y0, x1, y1); // 10;
    nonZeroCount = pixelSumAssign.getNonZeroCount(x0, y0, x1, y1); // 4;
    nonZeroAverage = pixelSumAssign.getNonZeroAverage(x0, y0, x1, y1); // 10;

    testCases.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1,
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
}

TestCases::~TestCases() {}

void TestCases::run()
{
    int numTestCases = testCases.size();
    int numTestPassed = 0;
    std::cout<<"----------Testing PixelSum interface methods-------------"<<std::endl;
    for (int i = 0; i < testCases.size(); i++)
    {
        testCases[i].run();
        if (testCases[i].passed)
            numTestPassed++;
    }
    std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "PixelSum tests completed. Passed: "<< numTestPassed<< "/" << numTestCases << std::endl;
    std::cout<<"----------Testing Swap Points function-------------"<<std::endl;
    testSwapPoints.run();
    std::cout<<"----------Testing Clamp border points function-------------"<<std::endl;
    testClampBorderPoints.run();


}
