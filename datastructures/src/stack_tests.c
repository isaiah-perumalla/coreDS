#include "tinytest.h"
#include <stdlib.h>
#include "stack.h"


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

  poped_value = (int*)Stack_pop(stack);
  ASSERT_EQUALS(&x1, poped_value);
  ASSERT("stack should be empty when all elements popped", Stack_isEmpty(stack));

  Stack_dispose(&stack);
  ASSERT_EQUALS(NULL, stack);
}

int main()
{
  RUN(test_push_pop_from_stack);
  return TEST_REPORT();
}
