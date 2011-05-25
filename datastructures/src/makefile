CFLAGS = -O0 -g -Wall -I../../tinytest  -pg

.PHONY: clean test

all:c_stack.o  stack_tests

stack_tests: c_stack.o 

test: stack_tests
	./stack_tests

clean:
	rm -f *.o gmon.out *.out *.aux stack_tests
