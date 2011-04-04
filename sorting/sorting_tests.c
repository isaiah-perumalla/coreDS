#include "../tinytest/tinytest.h"
#include "sort.h"

void test_bottom_up_merge_sort()
{
  int size = 5;
  int arry[] = {6,1,4,2,-1};
  int expected[]={-1,1,2,4,6};
  merge_sort_bottom_up(arry, size);
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

void test_all_on_large_input()
{
  int (*sort_functions[])(int* a, int size) = {merge_sort_bottom_up, insertion_sort };
  int i, size=2;
  for(i=0; i<size;i++) { 
    test_sort_large_input(sort_functions[i]);
  }
  
}
/* test runner */
int main()
{
  RUN(test_bottom_up_merge_sort);
  RUN(test_all_on_large_input);
  return TEST_REPORT();
}
