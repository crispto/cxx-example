.PHONY: run cmake build clean
run:
	./build/main
perf:
# 1. 使用不带优化的编译选项编译程序
	g++ -O0 -pg main.cpp 
# 2. 运行程序, 产生 gmon.out 文件
	./a.out
# 3. 使用 gprof 生成分析报告
	gprof  ./a.out gmon.out |gprof2dot  -w |dot -Gdpi=200 -Tpng -o out.png
cmake: clean
	test ! -e build &&  mkdir build
	cd build && cmake ..

build: cmake
	cd build && make -j4

clean:
	rm -rf build
