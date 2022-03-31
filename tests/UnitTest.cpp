//
// Created by Mostafa Mansour on 3/28/22.
//

#include "UnitTest.h"
#include "../PixelSum.h"
#include <iostream>
#include <chrono>
#include <iomanip>

UnitTest::UnitTest(const TestData& data) :testData(data) {}

void UnitTest::run()
{
    // parse the data from unsigned char* to std::vector<unsigned vector>
    unsigned char* buffer = new unsigned char[testData.buffer.size()];
    std::copy(testData.buffer.begin(), testData.buffer.end(), buffer);

    // Create PixelSum object
    PixelSum pixelSum(buffer, testData.xWidth, testData.yHeight);
    delete[] buffer;
    // Get the queries
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int pixSum = pixelSum.getPixelSum(testData.x0, testData.y0, testData.x1, testData.y1);
    double pixAvg = pixelSum.getPixelAverage(testData.x0, testData.y0, testData.x1, testData.y1);
    int nonZeroCount = pixelSum.getNonZeroCount(testData.x0, testData.y0, testData.x1, testData.y1);
    double nonZeroAverage = pixelSum.getNonZeroAverage(testData.x0, testData.y0, testData.x1, testData.y1);
    auto end = std::chrono::high_resolution_clock::now();
    double preprocessingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    preprocessingTime *= 1e-9;

    // Test Results
    std::cout<<"Test-----> "<<testData.name<< std::endl;
    passed = check(pixSum, pixAvg, nonZeroCount, nonZeroAverage);
    std::cout << "Time of 4 queries: " << std::setprecision(6) << preprocessingTime << "s" << std::endl;
    std::cout << "Obtained Sum: "<< pixSum << " -- Expected: "<<testData.pixelSum<< std::endl;
    std::cout << "Obtained Avg: "<< pixAvg << " -- Expected: "<<testData.pixelAvg<< std::endl;
    std::cout << "Obtained Non Zero Count: "<<nonZeroCount<<" -- Expected: "<<testData.nonZeroCount<< std::endl;
    std::cout << "Obtained Non Zero Avg: " <<nonZeroAverage << " -- Expected: "<< testData.nonZeroAverage<< std::endl;
    if(passed)
        std::cout<<testData.name<<" :Passed."<< std::endl;
    else
        std::cout<<testData.name<<" Failed."<<std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
}

bool UnitTest::check(unsigned int& pixSum, double& pixAvg, int& nonZeroCount, double& nonZeroAverage) const
{
    return (pixSum == testData.pixelSum) && (nonZeroCount == testData.nonZeroCount) && compare(pixAvg, testData.pixelAvg) && compare(nonZeroAverage, testData.nonZeroAverage);
}

