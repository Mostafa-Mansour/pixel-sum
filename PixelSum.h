//
// Created by Mostafa Mansour on 3/27/22.
//

#ifndef PIXELSUM_PIXELSUM_H
#define PIXELSUM_PIXELSUM_H


#include <vector>
#include <memory>

class PixelSum {

  /*
   * PixelSum.h is a header file for PixelSum class. The class is responsible for:
   *    1- Implementing a Sum Area Table
   *    2- Getting queries from the table.
   *
   * Class Members:
   *
   * Public:
   *    getPixelSum : A function to compute the pixel some in a given window.
   *    getPixelAverage: A function to compute the average of pixels within a given window. Average = sum_of_pixels/number_of_pixels_in_window
   *    getNonZeroCount: A function to compute the number of non zero pixels within a given window.
   *    getNonZeroAverage: A function to compute the average of non zeros pixels in a given window. Average = sum_of_pixels/sum_non_zero_pixels
   *    width: return the buffer width.
   *    height: return the buffer height.
   *    getSrcPt: return srcPtr. srcPtr is a pointer to the input buffer (shallow copy from the input buffer).
   *    getNonZeroSumTable: return nonZeroSumTable (see private members).
   *    getNonZeroTable: return nonZeroTable (see private members).
   *    getSumAreaTable: return sumAreaTable (see private members).
   *    swapPoints: A function to swap the coordinates of the query window if needed.
   *    clampBorderPoints: A function to clamp the window coordinates if needed (for coordinates out of the buffer range).
   *
   * private:
   *    bufferWidth: Buffer width. The width of the buffer at which srcPtr is pointing.
   *    bufferHeight: Buffer Height. The height of the buffer at which srcPtr is pointing.
   *    srcPtr: A shallow copy of the input buffer (pointer).
   *    nonZeroTable: Data structure for non zero elements where each non zero pixel in the buffer represented by 1.
   *    sumAreaTable: Data structure for Sum Area Table algorithm. Each point contain the sum of the pixels up and to the left from that point (given 2D image).
   *    nonZeroSumTable: Data structure for Sum Area Table algorithm applied on nonZeroTable. Each point contain the sum of the pixels up and to the left from that point (given 2D image).
   *
   *    computeSumAreaTable: A function implements Sum Area Table algorithm and saves the values in sumAreaTable. More information about the algorithm can be found in (https://www.geeksforgeeks.org/submatrix-sum-queries/).
   *    computeNonZeroSumTable: A function implements Sum Area Table algorithm for NonZeroTable and saves the values in nonZeroSumTable.
   *    getNumPixels: A function to compute the number of pixels within a given window.
   *    getSubTableSum: A function to compute the sum query of a sub matrix from sumAreaTable. More information (https://www.geeksforgeeks.org/summed-area-table-submatrix-summation/)
   *    frstRowCp, colWiseAdd, rowWiseAdd: Intermediate functions to compute sumAreaTable. More information (https://www.geeksforgeeks.org/submatrix-sum-queries/)
   *
   *
   *
   *
   */

public:
    PixelSum (const unsigned char* buffer, int xWidth, int yHeight);
    ~PixelSum (){};
    PixelSum (const PixelSum&);
    PixelSum& operator= (const PixelSum&);

    unsigned int getPixelSum (int x0, int y0, int x1, int y1) const;
    double getPixelAverage (int x0, int y0, int x1, int y1) const;

    int getNonZeroCount (int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage (int x0, int y0, int x1, int y1) const;

    int width() const{return bufferWidth;};
    int height() const{return bufferHeight;};

    const unsigned char* getSrcPtr() const{return srcPtr;};
    std::vector<int> getNonZeroSumTable() const {return nonZeroSumTable;}
    std::vector<unsigned char> getNonZeroTable() const {return nonZeroTable;}
    std::vector<unsigned int> getSumAreaTable() const{return sumAreaTable;}

  void swapPoints(int&, int&, int&, int&) const;
  void clampBorderPoints(int&, int&, int&, int&) const;


private:
    int bufferWidth;
    int bufferHeight;
    unsigned const char* srcPtr;
    std::vector<unsigned char> nonZeroTable; // unsigned char is enough for 0 or 1 values.
    std::vector<unsigned int> sumAreaTable; // unsigned int is enough as the max possible value is 255*4096*4096
    std::vector<int>nonZeroSumTable;        // max value of an element is 4096*4096

    void computeSumAreaTable();
    void computeNonZeroSumTable(size_t);
    unsigned int getNumPixels(int, int , int ,int) const;

    template<typename T>
    unsigned int getSubTableSum(const T&, int, int, int, int) const;
    template<typename T, typename U>
    void frstRowCp(T&, U&);
    template<typename T, typename U>
    void colWiseAdd(T&, U&);
    template<typename T>
    void rowWiseAdd(T&);








};


#endif //PIXELSUM_PIXELSUM_H
