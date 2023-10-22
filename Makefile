.PHONY: clean build install

build: clean
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_INSTALL_PREFIX=./install
	cmake --build build
build-only:
	cmake --build build
clean:
	rm -rf build install

install: build
	cmake --install build

run:
	./build/bin/${cmd}
