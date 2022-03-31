//
// Created by Mostafa Mansour on 3/30/22.
//

#include "TestClampBorderPoints.h"
#define MAX_DIMENSION 4096

std::string printWindowCoordinatesForClampingFunction(const std::vector<int>& windowCoordinates){
  std::string str="{";
  for(auto itr = windowCoordinates.begin(); itr != windowCoordinates.end(); itr++){
    str += std::to_string(*itr)+" ";
  }
  str +="}";
  return str;

}
TestClampBorderPoints::TestClampBorderPoints(std::vector<std::vector<int>> & borderPointsBeforeClamping,
                                             std::vector<std::vector<int>> & borderPointsAfterClamping,
                                             std::vector<std::string> & testCasesNames) :
                                             borderPointsBeforeClamping(borderPointsBeforeClamping),
                                             borderPointsAfterClamping(borderPointsAfterClamping), testCasesNames(testCasesNames) {


}
std::vector<int> TestClampBorderPoints::getClampResults(std::vector<int>& testVec, PixelSum& pixelSum){
  int x0 = testVec[0];
  int y0 = testVec[1];
  int x1 = testVec[2];
  int y1 = testVec[3];

  pixelSum.clampBorderPoints(x0, y0, x1, y1);
  return std::vector<int>({x0,y0,x1,y1});

}

void TestClampBorderPoints::run(){
  const unsigned char* buffer = new unsigned char(0); // to be able to use PixelSum class
  PixelSum pixelSum(buffer, MAX_DIMENSION, MAX_DIMENSION);
  delete buffer;
  int countCases = borderPointsBeforeClamping.size();

  if((borderPointsAfterClamping.size() != countCases) || (testCasesNames.size() != countCases))
    throw std::invalid_argument("Make sure that the dimensions of the cases are the same");

  int countPassed = 0;
  for(int i=0; i < countCases; i++){
    auto res = getClampResults(borderPointsBeforeClamping[i],pixelSum);
    if( res == borderPointsAfterClamping[i]){
      countPassed++;
      std::cout<<"Test-----> Case "<<i+1<<": "<<testCasesNames[i]<<": passed."<<std::endl;
    }
    else{
      std::cerr<<"Test-----> Case "<<i+1<<": "<<testCasesNames[i]<<": failed."<<"Expected"<< printWindowCoordinatesForClampingFunction(borderPointsAfterClamping[i]) <<"-obtained"<<printWindowCoordinatesForClampingFunction(res)<<std::endl;
    }
  }
  std::cout<<"Clamping borders tests completed. Passed: "<< countPassed<<"/"<<countCases<<"."<<std::endl;
}