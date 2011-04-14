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
  int size = 500000;
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

void test_binary_search_element_not_found()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  
  ASSERT_EQUALS(~b_search(103, arry,size), 10);
  ASSERT_EQUALS(~b_search(1, arry,size), 0);  
  ASSERT_EQUALS(~b_search(11, arry,size), 1);  
  int a[]={1,4,6};
  int index = ~b_search(2,a,3);
  ASSERT_EQUALS(index, 1);
}

void  test_binary_search_find_specified_element()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  ASSERT_EQUALS(b_search(90, arry,size), 3);
  int index = b_search(12, arry,size);
  ASSERT_EQUALS(index, 1);  
  index = b_search(101, arry,size);
  ASSERT_EQUALS(arry[index], 101);      
}

void test_merge_sort_bottom_up()
{
  test_sort_small_input(merge_sort_bottom_up);
  test_sort_large_input(merge_sort_bottom_up);
}

void test_binary_insertion_sort()
{
  test_sort_small_input(binary_insertion_sort);
  test_sort_large_input(binary_insertion_sort);
}
  
void test_insertion_sort()
{
  test_sort_small_input(insertion_sort);
  //  test_sort_large_input(insertion_sort);
}

/* test runner */
int main()
{
  RUN(test_merge_sort_bottom_up);
  //  RUN(test_insertion_sort);
  RUN(test_binary_insertion_sort);
  //  RUN(test_binary_search_find_specified_element);
  return TEST_REPORT();
}
