CFLAGS = -O0 -g -Wall -I../tinytest -I../datastructures/include  -pg
VPATH = ../datastructures/src
DATAOBJS := stack.o
.PHONY: clean test

all: $(DATAOBJS) sort.o  sorting_tests

sorting_tests: $(DATAOBJS) sort.o  

test: sorting_tests
	./sorting_tests

clean:
	rm -f *.o gmon.out *.out *.aux sorting_tests
