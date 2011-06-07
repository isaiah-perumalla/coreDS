CFLAGS = -O0 -g -Wall -I../../tinytest -Iinclude   -pg

.PHONY: clean test

all:stack.o heap.o  stack_tests

stack_tests: stack.o heap.o 

test: stack_tests
	./stack_tests

clean:
	rm -f *.o gmon.out *.out *.aux stack_tests
