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
  /*
   * Class to implement unit test for Swap points function.
   */

 public:
  TestSwapPoints(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&,std::vector<std::string>& );
  std::vector<std::vector<int>> pointsBeforeSwap;
  std::vector<std::vector<int>> expectedPointsAfterSwap;
  std::vector<std::string> testCasesNames;
  std::vector<int> getSwapResults(std::vector<int>& , PixelSum&);
  void run();

};



#endif //PIXELSUM_TESTSWAPPOINTS_H
