

build:clean
	mkdir build
	cd build && cmake .. && make

clean:
	rm -rf build
run:
	cd build && ./pixelsum


