//
// Created by Mostafa Mansour on 3/27/22.
//
#include <iostream>
#include "PixelSum.h"

PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int yHeight){
  /*
   * Class constructor
   * @param buffer: pointer to a gray scale image pixel.
   * @param xWidth: image width
   * @param yHeight: image height.
   *
   * The constructor instantiates different class members. It also check the validity of the buffer (not nullptr) and the dimensions (positive dimensions).
   * The constructor DOES NOT check that the dimensions matches the input image.
   *
   */
  if (xWidth * yHeight <= 0)
    throw std::invalid_argument("Invalid dimensions. The dimensions must be positive numbers");

  if (!buffer)
    throw std::invalid_argument("Buffer should not be a null pointer.");

  bufferWidth = xWidth;
  bufferHeight = yHeight;
  const size_t bufferPixelCount = (size_t)this->width() * this->height();
  srcPtr = buffer;

  nonZeroTable = std::vector<unsigned char>(bufferPixelCount);
  sumAreaTable = std::vector<unsigned int>(bufferPixelCount);
  nonZeroSumTable = std::vector<int>(bufferPixelCount);

  computeSumAreaTable();  // Implement Sum Area Table algorithm for the image
  computeNonZeroSumTable(bufferPixelCount); // Implement Sum Area Table algorithm for nonZeroTable
}

PixelSum::PixelSum(const PixelSum &other){
  this->srcPtr = other.getSrcPtr();
  this->bufferWidth = other.width();
  this->bufferHeight = other.height();
  const size_t bufferPixelCount = (size_t)this->width() * this->height();

  this->nonZeroTable = std::vector<unsigned char>(bufferPixelCount);
  this->sumAreaTable = std::vector<unsigned int>(bufferPixelCount);
  this->nonZeroSumTable = std::vector<int>(bufferPixelCount);

  this->nonZeroTable = other.getNonZeroTable();   // vector assignment operator makes deep copy
  this->sumAreaTable = other.getSumAreaTable();
  this->nonZeroSumTable = other.getNonZeroSumTable();
}

PixelSum& PixelSum::operator=(const PixelSum &other) {
  if(this != &other) {
    this->srcPtr = other.getSrcPtr();
    this->bufferWidth = other.width();
    this->bufferHeight = other.height();
    const size_t bufferPixelCount = (size_t)this->width() * this->height();;


    this->nonZeroTable.resize(bufferPixelCount);
    this->nonZeroSumTable.resize(bufferPixelCount);
    this->sumAreaTable.resize(bufferPixelCount);

    this->nonZeroTable = other.getNonZeroTable();   // vector assignment operator makes deep copy
    this->sumAreaTable = other.getSumAreaTable();
    this->nonZeroSumTable = other.getNonZeroSumTable();
  }
  return *this;
}

void PixelSum::computeSumAreaTable() {
  frstRowCp(sumAreaTable, srcPtr);
  colWiseAdd(sumAreaTable, srcPtr);
  rowWiseAdd(sumAreaTable);
}

void PixelSum::computeNonZeroSumTable(size_t bufferPixelCount) {
  // convert non zeros pixels to 1s
  for(size_t i=0; i < bufferPixelCount; i++){
    if(srcPtr[i] != 0)
      nonZeroTable[i] = 1;
    else
      nonZeroTable[i] = 0;
  }
  // construct Sum Area Table for non zero pixels.
  frstRowCp(nonZeroSumTable, nonZeroTable);
  colWiseAdd(nonZeroSumTable, nonZeroTable);
  rowWiseAdd(nonZeroSumTable);
}


template<typename T, typename U>
void PixelSum::frstRowCp(T& table, U& src) {
  for(int i = 0; i < this->width(); i++)
    table[i] = src[i];
}

template<typename T, typename U>
void PixelSum::colWiseAdd(T& table, U& src) {
  for(int row = 1; row < this->height(); row++)
    for(int col = 0; col < this->width(); col++)
      table[col + row*this->width()] = src[col + row*this->width()] + table[col + (row-1)*this->width()];
}

template<typename T>
void PixelSum::rowWiseAdd(T& table) {
  for(int row = 0; row < this->height(); row++)
    for(int col = 1; col < this->width(); col++)
      table[col + row*this->width()] += table[col-1 + row*this->width()];
}



int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
  swapPoints(x0, y0, x1, y1);
  if((x0 >= this->width()) && y0 >= this->height())
    return 0;
  clampBorderPoints(x0, y0, x1, y1);
  return (int)getSubTableSum(nonZeroSumTable, x0, y0, x1, y1);
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
  int nonZeroCount = getNonZeroCount(x0, y0, x1, y1);
  unsigned int pixelSum = getPixelSum(x0, y0,x1, y1);
  if(nonZeroCount == 0)
    return 0;
  return (double)pixelSum/nonZeroCount;

}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {
  swapPoints(x0, y0, x1, y1);
  if((x0 >= this->width()) && y0 >= this->height())
    return 0;
  clampBorderPoints(x0, y0, x1, y1);
  return getSubTableSum(sumAreaTable, x0, y0, x1, y1);
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const {
  unsigned int sum = getPixelSum(x0, y0, x1, y1);
  swapPoints(x0, y0, x1, y1);
  return (double)sum/getNumPixels(x0, y0, x1, y1);
}

template<typename T>
unsigned int PixelSum::getSubTableSum(const T& srcTable , int x0, int y0, int x1, int y1) const{
  unsigned int res = srcTable[x1 + y1*this->width()]; // the sum between (0,0) and (x1,y1)
  if(x0 > 0)
    res -= srcTable[(x0 - 1) + y1*this->width()];
  if(y0 > 0)
    res -= srcTable[x1 + (y0 - 1)*this->width()];
  if(x0 > 0 && y0 > 0)
    res += srcTable[x0 - 1 + (y0 - 1)*this->width()];
  return res;
}

unsigned int PixelSum::getNumPixels(int x0, int y0, int x1 , int y1) const{
  return (unsigned int)(x1 - x0 + 1) * (unsigned int)(y1 - y0 + 1);
}


void PixelSum::swapPoints(int &x0, int &y0, int &x1, int &y1) const {
  if(x0 > x1){
    int swapVar = x0;
    x0 = x1;
    x1 = swapVar;
  }
  if(y0 > y1){
    int swapVar = y0;
    y0 = y1;
    y1 = swapVar;
  }
}
void PixelSum::clampBorderPoints(int &x0, int &y0, int &x1, int &y1) const {
  x0 = (x0 < 0) ? 0:x0;
  x0 = (x0 >= this->width()) ? this->width()-1:x0;

  x1 = (x1 < 0) ? 0:x1;
  x1 = (x1 >= this->width()) ? this->width()-1:x1;

  y0 = (y0 < 0) ? 0:y0;
  y0 = (y0 >= this->height()) ? this->height()-1:y0;

  y1 = (y1 < 0) ? 0:y1;
  y1 = (y1 >= this->height()) ? this->height()-1:y1;
}
