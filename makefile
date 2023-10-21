.PHONY: clean build

build: clean
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build
build-only:
	cmake --build build
clean:
	rm -rf build

run: build-only
	./build/bin/${cmd}
