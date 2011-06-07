#include "gtest/gtest.h"
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


TEST(StackTest, PushPop) {
  Stack_T stack = Stack_new();
  ASSERT_TRUE(Stack_isEmpty(stack));
  
  int x1 = 1;
  int x2 = 2;
  Stack_push(&x1, stack);
  Stack_push(&x2, stack);
  
  int *poped_value = (int*)Stack_pop(stack);
  EXPECT_EQ(&x2, poped_value);

  poped_value = (int*)Stack_pop(stack);
  EXPECT_EQ(&x1, poped_value);
  EXPECT_TRUE( Stack_isEmpty(stack));

  Stack_dispose(&stack);
  EXPECT_EQ(NULL, stack);
}



TEST(HeapTest, InsertRemove) {

  int size =10;
  Heap_T heap = Heap_new(size, MAX_HEAP, compare_int);
  int x1,x2, x3;
  x1 =25; x2 = 30; x3 = 20;
  Heap_insert(&x1, heap);
  Heap_insert(&x2, heap);
  Heap_insert(&x3, heap);
  
  int* value = (int*)Heap_remove(heap);
  EXPECT_EQ(&x2, value);

  
  value = (int*)Heap_remove(heap);
  EXPECT_EQ(&x1, value);

  value = (int*)Heap_remove(heap);
  EXPECT_EQ(&x3, value);
  Heap_dispose(&heap);
  
}


TEST(HeapTest, InsertRemoveLargeInput)
{
  int size = 1000;
  int arry[size];
  int expected_arry[size];
  Heap_T heap = Heap_new(size, MIN_HEAP, compare_int);
  int i,j =0;
  for(i=size-1; i >=0; i--) {
    arry[j] = i;
    expected_arry[i] = i;
    Heap_insert(&arry[j++], heap);
  }
  for(i=0; i<size; i++) {
    int* val = (int*)Heap_remove(heap);
    EXPECT_EQ(expected_arry[i], *val);
  }
  Heap_dispose(&heap);
}

/*void test_build_heap()
{
  int size =1000;
  int arry[size];
  int j=0;
  for(i=size-1; i >=0; i--) {
    arry[j] = i;
    }

*/
