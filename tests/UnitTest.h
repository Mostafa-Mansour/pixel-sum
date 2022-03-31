//
// Created by Mostafa Mansour on 3/28/22.
//

#ifndef PIXELSUM_UNITTEST_H
#define PIXELSUM_UNITTEST_H

#include <string>
#include <vector>
#include "cmath"

static bool compare(double a, double b, double epsilon = 0.001){return (std::fabs(a - b) < epsilon);} //for floating point precision (average functions_

struct TestData
{
    /*
     * struct to pack the input data and the expected results.
     */
    // name
    std::string name;
    // data
    int xWidth;
    int yHeight;
    std::vector<unsigned char> buffer;
    int x0;
    int y0;
    int x1;
    int y1;
    // results
    unsigned int pixelSum;
    double pixelAvg;
    int nonZeroCount;
    double nonZeroAverage;
};

class UnitTest
{
  /*
   * A header for UnitTest class.
   * The class accepts an instance from TestData struct, run the tests, and compare the results.
   */
public:
    UnitTest(const TestData& testData);
    ~UnitTest(){};
    void run();
    bool check(unsigned int& pixSum, double& pixAvg, int& nonZeroCount, double& nonZeroAverage) const;
    TestData testData;
    bool passed;
};
#endif //PIXELSUM_UNITTEST_H
