CFLAGS = -g -O0 -Wall -I../tinytest -pg

.PHONY: clean test

all:sort.o sorting_tests

sorting_tests: sort.o

test: sorting_tests
	./sorting_tests

clean:
	rm -f *.o *.out *.aux sorting_tests
