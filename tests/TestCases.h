//
// Created by Mostafa Mansour on 3/28/22.
//

#ifndef PIXELSUM_TESTCASES_H
#define PIXELSUM_TESTCASES_H


#include <vector>
#include "UnitTest.h"
#include "TestSwapPoints.h"
#include "TestClampBorderPoints.h"


class TestCases
{
public:
    TestCases();
    virtual ~TestCases();
    TestSwapPoints testSwapPoints;
    TestClampBorderPoints testClampBorderPoints;
    void run();
    std::vector<UnitTest> testCases;
};

#endif //PIXELSUM_TESTCASES_H
