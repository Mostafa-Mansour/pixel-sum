//
// Created by Mostafa Mansour on 3/30/22.
//

#ifndef PIXELSUM_TESTCLAMPBORDERPOINTS_H
#define PIXELSUM_TESTCLAMPBORDERPOINTS_H

#include <iostream>
#include <vector>
#include "../PixelSum.h"
#include <string>

class TestClampBorderPoints {
 public:
  TestClampBorderPoints(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&,std::vector<std::string>& );
  std::vector<std::vector<int>> borderPointsBeforeClamping;
  std::vector<std::vector<int>> borderPointsAfterClamping;
  std::vector<std::string> testCasesNames;
  std::vector<int> getClampResults(std::vector<int>& , PixelSum&);
  void run();
};

#endif //PIXELSUM_TESTCLAMPBORDERPOINTS_H
