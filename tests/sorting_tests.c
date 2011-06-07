#include "tinytest.h"
#include "sort.h"
#include "search.h"
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

#define ASCENDING_ORDER true
#define DESCENDING_ORDER false


#define FAIL_UNLESS_ARRAY_EQUALS(expected, actual, length) if(memcmp(expected, actual, length) != 0) return false

#define TEST_SORTING(_sort_fn)  do \
    {   ASSERT((#_sort_fn),test_sort_small_input(_sort_fn));\
        ASSERT((#_sort_fn),test_sort_large_input(_sort_fn));\
    } while(0)
 

void  merge(void* dest, void* source, int sindex, int mid, int endindex, size_t esize, compare_fn compare);
void  merge_ascending(void* destArry, void* sourceArry, int sindex, int endindex, 
		      size_t esize, compare_fn compare);
void  merge_bitonic_seq(bool isAscending,void* destArry, void* sourceArry, int sindex, int endindex, 
			size_t esize, compare_fn compare);

static int compare_int(const void* key1, const void* key2)
{
  int a, b;
  a = *(const int*) key1;
  b = *(const int*) key2;
  if(a>b) return 1;
  else if( a<b) return -1;
  return 0;
}


bool test_sort_small_input(sort_fn sort_function)
{
  Stack_T stack = Stack_new();
  Stack_dispose(&stack);
  int size = 5;
  int arry[] = {6,1,4,2,-1};
  int expected[]={-1,1,2,4,6};
  
  sort_function(arry, size, sizeof(int), compare_int);

  FAIL_UNLESS_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
  
  int dup[] = {4,1,1,1,1};
  int exp[] = {1,1,1,1,4};
  sort_function(dup, size, sizeof(int), compare_int);
  FAIL_UNLESS_ARRAY_EQUALS(exp, dup, sizeof(int)*size); 
  return true;
}

void test_basic_merge()
{
  int arry[] = {8,9,10,11, 3,7,15};
  int expected[] = {8,9,3,7,10,11,15};
  int output[] = {8,9,10,11, 3,7,15};
  merge(output,arry, 2, 3,6, sizeof(int), compare_int);
  ASSERT_ARRAY_EQUALS(expected, output, sizeof(int)*7); 

  int ordered_array[] = {3,7,8,9,10,11,15};
  merge(output,expected, 0, 1,6, sizeof(int), compare_int);
  ASSERT_ARRAY_EQUALS(ordered_array, output, sizeof(int)*7); 
}

void test_ascending_and_descending_merge()
{
  int bitonic_seq[] = {8,9,15,17, 16, 12, 4};
  int expected_ascending[] = {4,8,9,12,15,16,17};
  int expected_descending[] = {17,16,15,12,9,8,4};
  int output[7];
  
  merge_bitonic_seq(ASCENDING_ORDER,output, bitonic_seq, 0, 6, sizeof(int), compare_int);
  ASSERT_ARRAY_EQUALS(expected_ascending, output, sizeof(int)*7);
  
  int desc_bitonic_seq[] = {17,15,9,8, 4,12,16};
  
  merge_bitonic_seq(DESCENDING_ORDER,output, desc_bitonic_seq, 0, 6, sizeof(int), compare_int);
  ASSERT_ARRAY_EQUALS(expected_descending, output, sizeof(int)*7);
  
}


bool test_sort_large_input(sort_fn sort_function)
{
  int size = 5000;
  int arry[size], expected[size];
  int i,j;
  j =0;
  for(i=size-1; i >=0; i--) {
    arry[j++] = i;
  }
  for(i=0;i<size;i++)expected[i] =i;
  sort_function(arry, size, sizeof(int), compare_int);
  FAIL_UNLESS_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 
  return true;
}

void test_binary_search_element_not_found()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  int target  =103;
  size_t esize = sizeof(target);
   
  ASSERT_EQUALS(~binary_search(&target, arry,size, esize,compare_int ), 10);
  target=1;
  ASSERT_EQUALS(~binary_search(&target, arry,size, esize, compare_int), 0);  
  target= 11;
  ASSERT_EQUALS(~binary_search(&target, arry,size, esize, compare_int), 1);  
  int a[]={1,4,6};
  target=2;
  int index = ~binary_search(&target,a,3, esize, compare_int);
  ASSERT_EQUALS(index, 1);
}

void  test_binary_search_find_specified_element()
{
  int size = 10;
  int arry[] = {10,12,80,90,100,101,101,101,102,102};
  size_t esize = sizeof(int);
  ASSERT_EQUALS(binary_search(&arry[3], arry,size, esize, compare_int), 3);
  int index = binary_search(&arry[1], arry,size, esize, compare_int);
  ASSERT_EQUALS(index, 1);  
  index = binary_search(&arry[5], arry,size, esize, compare_int);
  ASSERT_EQUALS(arry[index], 101);      
  
}

void test_merge_sort_optimized()
{
  TEST_SORTING(merge_sort_optimized);
}


void test_merge_sort_bottom_up()
{
  TEST_SORTING(merge_sort_bottom_up);
}


void test_merge_sort_top_down()
{
  TEST_SORTING(merge_sort_top_down);
}

void test_binary_insertion_sort()
{
  TEST_SORTING(binary_ins_sort);
}
  
void test_insertion_sort()
{
  TEST_SORTING(ins_sort);
}


void test_basic_quick_sort()
{
  TEST_SORTING(basic_quick_sort);
}

void test_hybrid_quick_sort()
{
  TEST_SORTING(merge_sort_optimized);
}

void test_merge_sort_bitonic_no_copy()
{
  TEST_SORTING(merge_sort_optimized_bitonic);
}



/* test runner */
int main()
{
  RUN(test_merge_sort_bottom_up);
  RUN(test_merge_sort_top_down);
  RUN(test_insertion_sort);
  RUN(test_binary_insertion_sort);
  RUN(test_basic_quick_sort);  
  RUN(test_hybrid_quick_sort);  
  RUN(test_merge_sort_optimized);
  RUN(test_basic_merge);
  RUN(test_ascending_and_descending_merge);
  RUN(test_binary_search_find_specified_element);
  RUN(test_merge_sort_bitonic_no_copy);
  return TEST_REPORT();
}
