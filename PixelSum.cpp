//
// Created by Mostafa Mansour on 3/27/22.
//
#include <iostream>
#include "PixelSum.h"

PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int yHeight) : bufferWidth(xWidth), bufferHeight(yHeight){

    if (xWidth * yHeight <= 0) return;

    const size_t bufferPixelCount = this->width() * this->height();
    srcPtr = buffer;
    nonZeroPtr = std::vector<unsigned char>(bufferPixelCount);
    sumAreaTable = std::vector<unsigned int>(bufferPixelCount);
    nonZeroTable = std::vector<int>(bufferPixelCount);

    computeSumAreaTable();
    computeNonZeroTable(bufferPixelCount);

}

void PixelSum::computeSumAreaTable() {
    _frstRowCp(sumAreaTable, srcPtr);
    _colWiseAdd(sumAreaTable, srcPtr);
    _rowWiseAdd(sumAreaTable);

}

void PixelSum::computeNonZeroTable(size_t bufferPixelCount) {

    // convert non zeros pixels to 1s
    for(unsigned int i=0; i < bufferPixelCount; i++){
        if(srcPtr[i] != 0)
            nonZeroPtr[i] = 1;
        else
            nonZeroPtr[i] = 0;
    }

    // construct Sum Area Table for non zero pixels.
    _frstRowCp(nonZeroTable, nonZeroPtr);
    _colWiseAdd(nonZeroTable, nonZeroPtr);
    _rowWiseAdd(nonZeroTable);

}


template<typename T, typename U>
void PixelSum::_frstRowCp(T& table, U& src) {
    for(int i = 0; i < this->width(); i++)
        table[i] = src[i];
}

template<typename T, typename U>
void PixelSum::_colWiseAdd(T& table, U& src) {
    for(int row = 1; row < this->height(); row++)
        for(int col = 0; col < this->width(); col++)
            table[col + row*this->width()] = src[col + row*this->width()] + table[col + (row-1)*this->width()];

}

template<typename T>
void PixelSum::_rowWiseAdd(T& table) {
    for(int row = 0; row < this->height(); row++)
        for(int col = 1; col < this->width(); col++)
            table[col + row*this->width()] += table[col-1 + row*this->width()];
}



int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
    swapPoints(x0, y0, x1, y1);
    clampBorderPoints(x0, y0, x1, y1);
    return (int)getSubTableSum(nonZeroTable, x0, y0, x1, y1);
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
    int nonZeroCount = getNonZeroCount(x0, y0, x1, y1);
    unsigned int pixelSum = getPixelSum(x0, y0,x1, y1);
    return (double)pixelSum/nonZeroCount;

}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {

    swapPoints(x0, y0, x1, y1);
    clampBorderPoints(x0, y0, x1, y1);
    return getSubTableSum(sumAreaTable, x0, y0, x1, y1);

}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const {
    unsigned int sum = getPixelSum(x0, y0, x1, y1);
    swapPoints(x0, y0, x1, y1);

    return (double)sum/_getNumPixels(x0, y0, x1, y1);
}

template<typename T>
unsigned int PixelSum::getSubTableSum(const T& srcTable , int x0, int y0, int x1, int y1) const{

    if(y0 == y1){ // it is a line, not bounding box
        std::cerr<<"Invalid box, y0 = y1"<<std::endl;
        return 0;
    }

    unsigned int res = srcTable[y1 + x1*this->width()]; // the sum between (0,0) and (x1,y1)

    if(x0 > 0)
        res -= srcTable[y1 + (x0 - 1)*this->width()];
    if(y0 > 0)
        res -= srcTable[y0 - 1 + x1*this->width()];
    if(x0 > 0 && y0 > 0)
        res += srcTable[y0 - 1 + (x0 - 1)*this->width()];

    return res;


}

unsigned int PixelSum::_getNumPixels(int x0, int y0, int x1 , int y1) const{

    return (x1 - x0 + 1) * (y1 - y0 + 1);
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
int PixelSum::height() const {return bufferHeight;}
int PixelSum::width() const {return bufferWidth;}