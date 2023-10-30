package main

import "fmt"

type Context struct {
	ch   chan int
	a    int
	name string
}

func main() {
	var c Context
	fmt.Printf("ch len : %d\n", len(c.ch))

	fmt.Printf("ch is nil: %v\n", c.ch == nil)

}
