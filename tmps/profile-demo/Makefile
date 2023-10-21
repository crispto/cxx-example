.PHONY: run cmake build clean
run:
	./build/main
perf:
	g++ -O0 -pg main.cpp
	-rm gmon.out
	./a.out
	gprof  ./a.out gmon.out |gprof2dot  -w |dot -Gdpi=200 -Tpng -o out.png
cmake: clean
	test ! -e build &&  mkdir build
	cd build && cmake ..

build: cmake
	cd build && make -j4

clean:
	rm -rf build