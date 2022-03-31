cmake_minimum_required(VERSION 3.13)
project(pixelSum)

set(CMAKE_CXX_STANDARD 17)


add_executable(pixelSum
        main.cpp
        PixelSum.cpp
        PixelSum.h
        tests/TestCases.cpp
        tests/TestCases.h
        tests/UnitTest.cpp
        tests/UnitTest.h
        tests/TestSwapPoints.cpp tests/TestSwapPoints.h tests/dataForTestSwapPoints.h tests/TestClampBorderPoints.cpp tests/TestClampBorderPoints.h tests/dataForTestClampBorderPoints.h)