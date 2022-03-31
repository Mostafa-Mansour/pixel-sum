//
// Created by Mostafa Mansour on 3/31/22.
//

#ifndef PIXELSUM_TESTSWAPPOINTS_H
#define PIXELSUM_TESTSWAPPOINTS_H

#include <iostream>
#include <vector>
#include "../PixelSum.h"
#include <string>


class TestSwapPoints{

 public:
  TestSwapPoints(std::vector<const std::vector<int>>&, std::vector<const std::vector<int>>&,std::vector<const std::string>& );
  std::vector<const std::vector<int>> pointsBeforeSwap;
  std::vector<const std::vector<int>> expectedPointsAfterSwap;
  std::vector<const std::string> testCasesNames;
  const std::vector<int> getSwapResults(const std::vector<int>& , PixelSum&);
  void run();

};



#endif //PIXELSUM_TESTSWAPPOINTS_H
