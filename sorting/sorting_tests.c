#include "tinytest.h"
#include "sort.h"
#include "search.h"
#include <stdlib.h>

bool test_sort_small_input(int (*sort_function) (int* a, int size))
{
  int size = 5;
  int arry[] = {6,1,4,2,-1};
  int expected[]={-1,1,2,4,6};
  
  sort_function(arry, size);

  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
  
  int dup[] = {4,1,1,1,1};
  int exp[] = {1,1,1,1,4};
  sort_function(dup, size);
  ASSERT_ARRAY_EQUALS(exp, dup, sizeof(int)*size); 
  return true;
  
}

void test_sort_input_mostly_duplicates(int (*sort_function)(int* a, int size))
{


  
}

bool test_sort_large_input(int (*sort_function)(int* a, int size))
{
  int size = 5;
  int arry[size], expected[size];
  int i,j;
  j =0;
  for(i=size-1; i >=0; i--) {
    arry[j++] = i;
  }
  for(i=0;i<size;i++)expected[i] =i;
  sort_function(arry, size);
  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
  return true;
}

bool test_binary_search_element_not_found()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  
  ASSERT_EQUALS(~b_search(103, arry,size), 10);
  ASSERT_EQUALS(~b_search(1, arry,size), 0);  
  ASSERT_EQUALS(~b_search(11, arry,size), 1);  
  int a[]={1,4,6};
  int index = ~b_search(2,a,3);
  ASSERT_EQUALS(index, 1);
  return true;
}

bool  test_binary_search_find_specified_element()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  ASSERT_EQUALS(b_search(90, arry,size), 3);
  int index = b_search(12, arry,size);
  ASSERT_EQUALS(index, 1);  
  index = b_search(101, arry,size);
  ASSERT_EQUALS(arry[index], 101);      
  return true;
}

static int compare_int(const void* key1, const void* key2)
{
  int a, b;
  a = *(const int*) key1;
  b = *(const int*) key2;
  if(a>b) return 1;
  else if( a<b) return -1;
  return 0;
}

static int  _binary_insertion_sort(int* a, int size)
{
  return binary_ins_sort(a, size, sizeof(int), compare_int);
}

static int  _insertion_sort(int* a, int size)
{
  return ins_sort(a, size, sizeof(int), compare_int);
}

void test_merge_sort_bottom_up()
{
  test_sort_small_input(merge_sort_bottom_up);
  test_sort_large_input(merge_sort_bottom_up);
}

void test_binary_insertion_sort()
{
  if(!test_sort_small_input(_binary_insertion_sort)) return;
  test_sort_large_input(_binary_insertion_sort);
}
  
void test_insertion_sort()
{
  test_sort_small_input(_insertion_sort);
  test_sort_large_input(_insertion_sort);
}


void test_basic_quick_sort()
{
  test_sort_small_input(basic_quick_sort);
  test_sort_large_input(basic_quick_sort);
}

void test_hybrid_quick_sort()
{
  test_sort_small_input(quick_sort);
  test_sort_large_input(quick_sort);
}

/* test runner */
int main()
{
  RUN(test_merge_sort_bottom_up);
  RUN(test_insertion_sort);
  RUN(test_binary_insertion_sort);
  RUN(test_basic_quick_sort);  

  RUN(test_hybrid_quick_sort);  
  // RUN(test_binary_search_find_specified_element);

  return TEST_REPORT();
}
