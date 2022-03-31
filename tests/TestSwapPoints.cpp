//
// Created by Mostafa Mansour on 3/30/22.
//

#include <iostream>
#include <vector>
#include <string>
#include "TestSwapPoints.h"


std::string printWindowCoordinatesForSwapFunction(const std::vector<int>& windowCoordinates){
  std::string str="{";
  for(auto itr = windowCoordinates.begin(); itr != windowCoordinates.end(); itr++){
    str += std::to_string(*itr)+" ";
  }
  str +="}";
  return str;

}

TestSwapPoints::TestSwapPoints(std::vector<std::vector<int>> &pointsBeforeSwap,
                               std::vector<std::vector<int>> &expectedPointsAfterSwap,
                               std::vector<std::string> &testCasesNames) : pointsBeforeSwap(pointsBeforeSwap),
                               expectedPointsAfterSwap(expectedPointsAfterSwap), testCasesNames(testCasesNames){

}

 std::vector<int> TestSwapPoints::getSwapResults(std::vector<int>& testVec, PixelSum& pixelSum){
  int x0 = testVec[0];
  int y0 = testVec[1];
  int x1 = testVec[2];
  int y1 = testVec[3];

  pixelSum.swapPoints(x0, y0, x1, y1);
  std::vector<int> res({x0,y0,x1,y1});
  return res;

}

void TestSwapPoints::run(){
  std::vector<unsigned char> bufferVec({3,4,43,12,10,22}); // Dummy buffer to instantiate PixelSum class
  unsigned char* buffer = new unsigned char[bufferVec.size()];
  std::copy(bufferVec.begin(), bufferVec.end(), buffer);
  PixelSum pixelSum(buffer, 2, 3);
  delete[] buffer;
  int countCases = pointsBeforeSwap.size();

  if((expectedPointsAfterSwap.size() != countCases) || (testCasesNames.size() != countCases))
    throw std::invalid_argument("Make sure that the dimensions of the cases are the same");

  int countPassed = 0;
  for(int i=0; i < countCases; i++){
    auto res = getSwapResults(pointsBeforeSwap[i],pixelSum);
    if( res == expectedPointsAfterSwap[i]){
      countPassed++;
      std::cout<<"Test-----> Case "<<i+1<<": "<<testCasesNames[i]<<": passed."<<std::endl;
    }
    else{
      std::cerr<<"Test-----> Case "<<i+1<<": "<<testCasesNames[i]<<": failed."<<"Expected"<< printWindowCoordinatesForSwapFunction(expectedPointsAfterSwap[i]) <<"-obtained"<<printWindowCoordinatesForSwapFunction(res)<<std::endl;
    }
  }
  std::cout<<"Swap points tests completed. Passed: "<< countPassed<<"/"<<countCases<<"."<<std::endl;
}
