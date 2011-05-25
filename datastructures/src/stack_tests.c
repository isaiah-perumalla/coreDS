#include "tinytest.h"
#include <stdlib.h>
#include "c_stack.h"


void test_push_pop_from_stack()
{
  Stack_T stack = Stack_new();
  ASSERT("stack should be empty when created",Stack_isEmpty(stack));
  
  int x1 = 1;
  int x2 = 2;
  Stack_push(&x1, stack);
  Stack_push(&x2, stack);
  
  int *poped_value = (int*)Stack_pop(stack);
  ASSERT_EQUALS(&x2, poped_value);
  
}

int main()
{
  RUN(test_push_pop_from_stack);
  return TEST_REPORT();
}
