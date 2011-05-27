CFLAGS = -O0 -g -Wall -I../tinytest -I../datastructures/src  -pg
VPATH = src:../datastructures/src
.PHONY: clean test

all: stack.o sort.o  sorting_tests

sorting_tests: stack.o sort.o  

test: sorting_tests
	./sorting_tests

clean:
	rm -f *.o gmon.out *.out *.aux sorting_tests
