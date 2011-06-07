CFLAGS = -O0 -g -Wall -I../tinytest -pg

.PHONY: clean test

all:search.o searching_tests

searching_tests: search.o

test: searching_tests
	./searching_tests

clean:
	rm -f *.o gmon.out *.out *.aux sorting_tests
