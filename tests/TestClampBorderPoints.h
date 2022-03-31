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
  TestClampBorderPoints(std::vector<const std::vector<int>>&, std::vector<const std::vector<int>>&,std::vector<const std::string>& );
  std::vector<const std::vector<int>> borderPointsBeforeClamping;
  std::vector<const std::vector<int>> borderPointsAfterClamping;
  std::vector<const std::string> testCasesNames;
  const std::vector<int> getClampResults(const std::vector<int>& , PixelSum&);
  void run();
};

#endif //PIXELSUM_TESTCLAMPBORDERPOINTS_H
