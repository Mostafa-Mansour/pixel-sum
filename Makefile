

build:clean
	mkdir build
	cd build && cmake .. && make

build-debug:clean
	mkdir build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make
build-mem:clean
	mkdir build
	cd build && g++ -std=c++17  ../main.cpp ../PixelSum.cpp ../tests/UnitTest.cpp ../tests/TestCases.cpp ../tests/TestCases.h ../tests/UnitTest.cpp ../tests/UnitTest.h ../tests/TestSwapPoints.cpp ../tests/TestSwapPoints.h ../tests/dataForTestSwapPoints.h ../tests/TestClampBorderPoints.cpp ../tests/TestClampBorderPoints.h ../tests/dataForTestClampBorderPoints.h -g -o pixelsum
clean:
	rm -rf build
run:
	cd build && ./pixelsum


