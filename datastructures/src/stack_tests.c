#include "tinytest.h"
#include <stdlib.h>
#include "stack.h"
#include "heap.h"

int compare_int(const void* a, const void* b)
{
  return 0;
}


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


void test_insert_remove_from_heap()
{
  Heap_T heap = Heap_new(MAX_HEAP, compare_int);
  int x1,x2, x3;
  x1 =20; x2 = 30; x3 = 25;
  Heap_insert(&x1, heap);
  Heap_insert(&x2, heap);
  Heap_insert(&x3, heap);
  
  int* value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x2, value);

  value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x3, value);

  value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x1, value);
  
}

int main()
{
  RUN(test_push_pop_from_stack);
  return TEST_REPORT();
}
