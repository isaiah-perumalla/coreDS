#include "tinytest.h"
#include "sort.h"
#include <stdlib.h>

void test_sort_small_input(int (*sort_function) (int* a, int size))
{
  int size = 5;
  int arry[] = {6,1,4,2,-1};
  int expected[]={-1,1,2,4,6};
  sort_function(arry, size);
  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
}

void test_sort_large_input(int (*sort_function)(int* a, int size))
{
  int size = 5000;
  int arry[size], expected[size];
  int i,j;
  j =0;
  for(i=size-1; i >=0; i--) {
    arry[j++] = i;
  }

  for(i=0;i<size;i++)expected[i] =i;
  sort_function(arry, size);
  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
}

void test_merge_sort_bottom_up()
{
  test_sort_small_input(merge_sort_bottom_up);
  test_sort_large_input(merge_sort_bottom_up);
}
  
void test_insertion_sort()
{
  test_sort_small_input(insertion_sort);
  test_sort_large_input(insertion_sort);
}

/* test runner */
int main()
{
  RUN(test_merge_sort_bottom_up);
  RUN(test_insertion_sort);
  return TEST_REPORT();
}
