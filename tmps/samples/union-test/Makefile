.PHONY: build run cmake build
cmake: clean
	@cd build && cmake ..
build: 
	@cd build && make -j4
run: 
	@./build/$(cmd)_demo /home/richard/data/4v2l/50/000001.pcd
clean:
	@cd build && rm -rf *