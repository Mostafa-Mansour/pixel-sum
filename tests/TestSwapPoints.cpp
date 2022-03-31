//
// Created by Mostafa Mansour on 3/30/22.
//

#include <iostream>
#include <vector>
#include <string>
#include "TestSwapPoints.h"

#define MAX_DIMENSION 4096


std::string printWindowCoordinatesForSwapFunction(const std::vector<int>& windowCoordinates){
  std::string str="{";
  for(auto itr = windowCoordinates.begin(); itr != windowCoordinates.end(); itr++){
    str += std::to_string(*itr)+" ";
  }
  str +="}";
  return str;

}

TestSwapPoints::TestSwapPoints(std::vector<const std::vector<int>> &pointsBeforeSwap,
                               std::vector<const std::vector<int>> &expectedPointsAfterSwap,
                               std::vector<const std::string> &testCasesNames) : pointsBeforeSwap(pointsBeforeSwap),
                               expectedPointsAfterSwap(expectedPointsAfterSwap), testCasesNames(testCasesNames){

}

const std::vector<int> TestSwapPoints::getSwapResults(const std::vector<int>& testVec, PixelSum& pixelSum){
  int x0 = testVec[0];
  int y0 = testVec[1];
  int x1 = testVec[2];
  int y1 = testVec[3];

  pixelSum.swapPoints(x0, y0, x1, y1);
  return std::vector<int>({x0,y0,x1,y1});

}

void TestSwapPoints::run(){
  const unsigned char* buffer = new unsigned char(0); // to be able to use PixelSum class
  PixelSum pixelSum(buffer, MAX_DIMENSION, MAX_DIMENSION);

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