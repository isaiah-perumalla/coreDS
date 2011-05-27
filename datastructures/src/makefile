CFLAGS = -O0 -g -Wall -I../../tinytest -I../include   -pg

.PHONY: clean test

all:stack.o  stack_tests

stack_tests: stack.o 

test: stack_tests
	./stack_tests

clean:
	rm -f *.o gmon.out *.out *.aux stack_tests
