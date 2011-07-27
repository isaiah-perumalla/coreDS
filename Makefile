# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.

.PHONY: all tests
GTEST_DIR = gtest-1.6.0

# Where to find user code.
USER_DIR = src
TEST_DIR = tests
DATASTRUCTURES = $(USER_DIR)/datastructures/*.c  $(USER_DIR)/datastructures/include/*.h 
TEST_SRC = $(TEST_DIR)/*.c $(TEST_DIR)/*.cc
OUT_DIR = ./

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = all_unittests

OBJS = stack.o heap.o sort.o 
TEST_OBJS = stack_tests.o sorting_tests.o binaryheap_test.o
OUT_OBJS=$(addprefix $(OUT_DIR)/, $(OBJS))
OUT_TEST_OBJS=$(addprefix $(OUT_DIR)/, $(TEST_OBJS))
# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

INCLUDES = -I$(USER_DIR)/datastructures/include 

#LIBS = -L/usr/locacl/lib -lm
# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o $(USER_DIR)/datastructures/include/*.gch

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

$(OUT_OBJS)%.o : $(DATASTRUCTURES)  $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -c  $(DATASTRUCTURES)  

$(OUT_TEST_OBJS)%.o : $(GTEST_HEADERS) $(OUT_OBJS) $(TEST_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC)

all_unittests : $(OUT_OBJS) $(OUT_TEST_OBJS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

test: all_unittests
	./all_unittests