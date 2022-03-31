//
// Created by Mostafa Mansour on 3/31/22.
//

#ifndef PIXELSUM_DATAFORTESTCLAMPBORDERPOINTS_H
#define PIXELSUM_DATAFORTESTCLAMPBORDERPOINTS_H
#include <vector>
#include <string>
#define BUFFER_WIDTH 2
#define BUFFER_HEIGHT 3
// Test cases data for ClampBorders
std::vector<std::vector<int>> borderPointsBeforeClamping{
    // Test cases
    {0,1,0,1},  // one pixel
    {-10, -2, -9, -1},  // negative, both points are outside the buffer
    {5,4,BUFFER_WIDTH,BUFFER_HEIGHT},  // one point (both coordinates - equal to the maximum dimension) outside the buffer
    {4,10,BUFFER_WIDTH,2}, // one point (single coordinate - equal to the maximum dimension) out side the buffer
    {5,4,BUFFER_WIDTH+10,BUFFER_HEIGHT+10},  // one point (both coordinates) outside the buffer
    {4,10,BUFFER_WIDTH+10,2}, // one point (single coordinate) out side the buffer
    {0,0,0,0}, // one pixel at the upper left corner
    {BUFFER_WIDTH-1, BUFFER_HEIGHT-1, BUFFER_WIDTH-1, BUFFER_HEIGHT-1}, // one pixel at the lower right corner
    {BUFFER_WIDTH-1,0,BUFFER_WIDTH-1,0}, // one pixel at the upper right corner
    {0, BUFFER_HEIGHT-1, 0, BUFFER_HEIGHT-1}, // one pixel at the lower right corner
    {-10,-4, BUFFER_WIDTH, -3}, // outside rectangular window above the image
    {-10,4, -3, 4}, // outside rectangular window above to the left the image
    {-3,BUFFER_HEIGHT, 49, BUFFER_HEIGHT}, // outside rectangular window down from the image
    {BUFFER_WIDTH+10, 5, BUFFER_WIDTH+4, 8}, // outside rectangular window to the right of the image
};

std::vector<std::vector<int>> expectedBorderPointsAfterClamping{
    // Expected results
    {0,1,0,1},
    {0,0,0,0},
    {BUFFER_WIDTH-1,BUFFER_HEIGHT-1,BUFFER_WIDTH-1,BUFFER_HEIGHT-1},  // one point (both coordinates - equal to the maximum dimension) outside the buffer
    {BUFFER_WIDTH-1,BUFFER_HEIGHT-1,BUFFER_WIDTH-1,2}, // one point (single coordinate - equal to the maximum dimension) out side the buffer
    {BUFFER_WIDTH-1,BUFFER_HEIGHT-1,BUFFER_WIDTH-1,BUFFER_HEIGHT-1},  // one point (both coordinates) outside the buffer
    {BUFFER_WIDTH-1,BUFFER_HEIGHT-1,BUFFER_WIDTH-1,2}, // one point (single coordinate) out side the buffer
    {0,0,0,0}, // one pixel at the upper left corner
    {BUFFER_WIDTH-1, BUFFER_HEIGHT-1, BUFFER_WIDTH-1, BUFFER_HEIGHT-1}, // one pixel at the lower right corner
    {BUFFER_WIDTH-1,0,BUFFER_WIDTH-1,0}, // one pixel at the upper right corner
    {0, BUFFER_HEIGHT-1, 0, BUFFER_HEIGHT-1}, // one pixel at the lower right corner
    {0,0, BUFFER_WIDTH-1, 0}, // outside rectangular window above the image
    {0,BUFFER_HEIGHT-1, 0, BUFFER_HEIGHT-1}, // outside rectangular window above to the left the image
    {0,BUFFER_HEIGHT-1, BUFFER_WIDTH-1, BUFFER_HEIGHT-1}, // outside rectangular window down from the image
    {BUFFER_WIDTH-1, BUFFER_HEIGHT-1, BUFFER_WIDTH-1, BUFFER_HEIGHT-1}, // outside rectangular window to the right of the image
};

std::vector<std::string> testCasesNamesForClamping{
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
