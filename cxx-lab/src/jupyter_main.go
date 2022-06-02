package main

//#cgo CFLAGS: -I ./home/richard/coding/github/laboratory/cxx-lab/install/include
//#cgo LDFLAGE: -L /home/richard/coding/github/laboratory/cxx-lab/install/lib -l labor
// #include "jupyter.h"

import "C"

func main() {
	C.printf("hello world\n")
	k := C.start()
	C.stop()
}
