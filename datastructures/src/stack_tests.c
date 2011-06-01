#include "tinytest.h"
#include <stdlib.h>
#include "stack.h"
#include "heap.h"
#include "mem.h"

static int compare_int(const void* key1, const void* key2)
{
  int a, b;
  a = *(const int*) key1;
  b = *(const int*) key2;
  if(a>b) return 1;
  else if( a<b) return -1;
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
  int size =10;
  Heap_T heap = Heap_new(size, MAX_HEAP, compare_int);
  int x1,x2, x3;
  x1 =25; x2 = 30; x3 = 20;
  Heap_insert(&x1, heap);
  Heap_insert(&x2, heap);
  Heap_insert(&x3, heap);
  
  int* value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x2, value);

  
  value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x1, value);

  value = (int*)Heap_remove(heap);
  ASSERT_EQUALS(&x3, value);
  
}

int main()
{
  RUN(test_push_pop_from_stack);
  RUN(test_insert_remove_from_heap);
  return TEST_REPORT();
}
