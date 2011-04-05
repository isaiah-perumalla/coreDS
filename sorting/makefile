CFLAGS = -g -O0 -Wall -I../tinytest

.PHONY: clean test

all:sort.o sorting_tests

sorting_tests: sort.o

test: sorting_tests
	./sorting_tests

clean:
	rm -f *.o sorting_tests
