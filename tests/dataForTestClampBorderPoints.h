//
// Created by Mostafa Mansour on 3/31/22.
//

#ifndef PIXELSUM_DATAFORTESTCLAMPBORDERPOINTS_H
#define PIXELSUM_DATAFORTESTCLAMPBORDERPOINTS_H
#include <vector>
#include <string>
#define MAX_WIDTH 4096L
#define MAX_HEIGHT 4096L
// Test cases data for ClampBorders
std::vector<const std::vector<int>> borderPointsBeforeClamping{
    // Test cases
    {0,1,0,1},  // one pixel
    {-10, -2, -9, -1},  // negative, both points are outside the buffer
    {5,4,MAX_WIDTH,MAX_HEIGHT},  // one point (both coordinates - equal to the maximum dimension) outside the buffer
    {4,10,MAX_WIDTH,2}, // one point (single coordinate - equal to the maximum dimension) out side the buffer
    {5,4,MAX_WIDTH+10,MAX_HEIGHT+10},  // one point (both coordinates) outside the buffer
    {4,10,MAX_WIDTH+10,2}, // one point (single coordinate) out side the buffer
    {0,0,0,0}, // one pixel at the upper left corner
    {MAX_WIDTH-1, MAX_HEIGHT-1, MAX_WIDTH-1, MAX_HEIGHT-1}, // one pixel at the lower right corner
    {MAX_WIDTH-1,0,MAX_WIDTH-1,0}, // one pixel at the upper right corner
    {0, MAX_HEIGHT-1, 0, MAX_HEIGHT-1}, // one pixel at the lower right corner
    {-10,-4, MAX_WIDTH, -3}, // outside rectangular window above the image
    {-10,4, -3, 4}, // outside rectangular window above to the left the image
    {-3,MAX_HEIGHT, 49, MAX_HEIGHT}, // outside rectangular window down from the image
    {MAX_WIDTH+10, 5, MAX_WIDTH+4, 8}, // outside rectangular window to the right of the image
};

std::vector<const std::vector<int>> expectedBorderPointsAfterClamping{
    // Expected results
    {0,1,0,1},
    {0,0,0,0},
    {5,4,MAX_WIDTH-1,MAX_HEIGHT-1},  // one point (both coordinates - equal to the maximum dimension) outside the buffer
    {4,10,MAX_WIDTH-1,2}, // one point (single coordinate - equal to the maximum dimension) out side the buffer
    {5,4,MAX_WIDTH-1,MAX_HEIGHT-1},  // one point (both coordinates) outside the buffer
    {4,10,MAX_WIDTH-1,2}, // one point (single coordinate) out side the buffer
    {0,0,0,0}, // one pixel at the upper left corner
    {MAX_WIDTH-1, MAX_HEIGHT-1, MAX_WIDTH-1, MAX_HEIGHT-1}, // one pixel at the lower right corner
    {MAX_WIDTH-1,0,MAX_WIDTH-1,0}, // one pixel at the upper right corner
    {0, MAX_HEIGHT-1, 0, MAX_HEIGHT-1}, // one pixel at the lower right corner
    {0,0, MAX_WIDTH-1, 0}, // outside rectangular window above the image
    {0,4, 0, 4}, // outside rectangular window above to the left the image
    {0,MAX_HEIGHT-1, 49, MAX_HEIGHT-1}, // outside rectangular window down from the image
    {MAX_WIDTH-1, 5, MAX_WIDTH-1, 8}, // outside rectangular window to the right of the image
};

std::vector<const std::string> testCasesNamesForClamping{
    "one pixel inside",
    "negative, both points are outside the buffer",
    "one point (both coordinates - equal to the maximum dimension) outside the buffer",
    "one point (single coordinate - equal to the maximum dimension) out side the buffer",
    "one point (both coordinates) outside the buffer",
   "one point (single coordinate) out side the buffer",
    "one pixel at the upper left corner",
    "one pixel at the lower right corner",
    "one pixel at the upper right corner",
    "one pixel at the lower right corner",
    "outside rectangular window above the image",
    "outside rectangular window above to the left the image",
    "outside rectangular window down from the image",
    "outside rectangular window to the right of the image"
};
#endif //PIXELSUM_DATAFORTESTCLAMPBORDERPOINTS_H
