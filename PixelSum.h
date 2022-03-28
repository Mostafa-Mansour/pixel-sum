//
// Created by Mostafa Mansour on 3/27/22.
//

#ifndef PIXELSUM_PIXELSUM_H
#define PIXELSUM_PIXELSUM_H


#include <sys/_types/_u_int.h>
#include <vector>
#include <memory>

class PixelSum {

public:


    PixelSum (const unsigned char* buffer, int xWidth, int yHeight);

    ~PixelSum (void){};

    PixelSum (const PixelSum&);
    PixelSum& operator= (const PixelSum&);

    unsigned int getPixelSum (int x0, int y0, int x1, int y1) const;
    double getPixelAverage (int x0, int y0, int x1, int y1) const;

    int getNonZeroCount (int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage (int x0, int y0, int x1, int y1) const;

    void computeSumAreaTable();


    int width() const;

    int height() const;



    void swapPoints(int&, int&, int&, int&) const;

    template<typename T>
    unsigned int getSubTableSum(const T&, int, int, int, int) const;
    void _frstRowCp();
    void _colWiseAdd();
    void _rowWiseAdd();
    unsigned int _getNumPixels(int, int , int ,int) const;

    std::vector<unsigned int>& getSumAreaTablePtr(){
        return sumAreaTable;
    }

private:
    int  bufferWidth;
    int bufferHeight;
    std::vector<unsigned int> sumAreaTable; // unsigned int is enough as the max possible value is 255*4096*4096
    std::vector<int>zerosTable;
    const unsigned char* srcPtr;






};


#endif //PIXELSUM_PIXELSUM_H
