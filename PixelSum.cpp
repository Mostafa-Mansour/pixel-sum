//
// Created by Mostafa Mansour on 3/27/22.
//
#include <iostream>
#include "PixelSum.h"

PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int yHeight) : bufferWidth(xWidth), bufferHeight(yHeight){

    if (xWidth * yHeight <= 0) return;

    const size_t bufferPixelCount = this->width() * this->height();
    srcPtr = buffer;
    sumAreaTable = std::vector<unsigned int>(bufferPixelCount);
    zerosTable = std::vector<int>(bufferPixelCount);

    computeSumAreaTable();

}

void PixelSum::computeSumAreaTable() {
    _frstRowCp();
    _colWiseAdd();
    _rowWiseAdd();

}

void PixelSum::_frstRowCp() {
    for(int i = 0; i < this->width(); i++)
        sumAreaTable[i] = srcPtr[i];
}

void PixelSum::_colWiseAdd() {
    for(int row = 1; row < this->height(); row++)
        for(int col = 0; col < this->width(); col++)
            sumAreaTable[col + row*this->width()] = srcPtr[col + row*this->width()] + sumAreaTable[col + (row-1)*this->width()];

}

void PixelSum::_rowWiseAdd() {
    for(int row = 0; row < this->height(); row++)
        for(int col = 1; col < this->width(); col++)
            sumAreaTable[col + row*this->width()] += sumAreaTable[col-1 + row*this->width()];
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {

    swapPoints(x0, y0, x1, y1);
    return getSubTableSum(sumAreaTable, x0, y0, x1, y1);

}

template<typename T>
unsigned int PixelSum::getSubTableSum(const T& srcTable , int x0, int y0, int x1, int y1) const{

    unsigned int res = srcTable[y1 + x1*this->width()]; // the sum between (0,0) and (x1,y1)

    if(x0 > 0)
        res -= srcTable[y1 + (x0 - 1)*this->width()];
    if(y0 > 0)
        res -= srcTable[y0 - 1 + x1*this->width()];
    if(x0 > 0 && y0 > 0)
        res += srcTable[y0 - 1 + (x0 - 1)*this->width()];

    return res;


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
int PixelSum::height() const {return bufferHeight;}
int PixelSum::width() const {return bufferWidth;}