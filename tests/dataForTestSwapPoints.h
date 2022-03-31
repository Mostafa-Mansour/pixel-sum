//
// Created by Mostafa Mansour on 3/31/22.
//

#ifndef PIXELSUM_DATAFORTESTSWAPPOINTS_H
#define PIXELSUM_DATAFORTESTSWAPPOINTS_H
// Test cases data for SwapFunction
std::vector<const std::vector<int>> pointsBeforeSwap{
    // Test cases
    {0,1,0,1},  // x0=x1, y0=y1
    {2,1,4,8},  // x1>x0, y1>y0
    {5,4,3,6},  // x1<x0, y1>y0
    {4,10,6,2}, // x1>x0, y1<y0
    {10,4,3,1}, // x1<x0, y1>y0
    {-4,-7,-2,-3}, // negative coordinates
};

std::vector<const std::vector<int>> expectedPointsAfterSwap{
    // Expected results
    {0,1,0,1},
    {2,1,4,8},
    {3,4,5,6},
    {4,2,6,10},
    {3,1,10,4},
    {-4,-7,-2,-3}
};

std::vector<const std::string> testCasesNames{
    "x0=x1, y0-y1",
    "x1>x0, y1>y0",
    "x1<x0, y1>y0",
    "x1>x0, y1<y0",
    "x1<x0, y1>y0",
    "negative coordinates"
};
#endif //PIXELSUM_DATAFORTESTSWAPPOINTS_H
