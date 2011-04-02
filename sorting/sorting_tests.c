
#include "../../tinytest/tinytest.h"
#include "sort.h"
#define ASSERT_ARRAY_EQUALS(expected, actual, size) ASSERT((#actual), memcmp((expected),(actual), (size)) == 0)
void test_bottom_up_merge_sort()
{
  int size = 5;
  int arry[] = {6,1,4,2,-1};
  int expected[]={-1,1,2,4,6};
  merge_sort_bottom_up(arry, size);
  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 

}

void test_bottom_up_merge_sort_stress()
{
  int size = 50000000;
  int arry[size], expected[size];
  int i,j;
  j =0;
  for(i=size-1; i >=0; i--) {
    arry[j++] = i;
  }
  for(i=0;i<size;i++)expected[i] =i;
  merge_sort_bottom_up(arry, size);

  ASSERT_ARRAY_EQUALS(expected, arry, sizeof(int)*size); 

}


/* test runner */
int main()
{
  //RUN(test_bottom_up_merge_sort);
  RUN(test_bottom_up_merge_sort_stress);
  return TEST_REPORT();
}
