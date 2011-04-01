
#include "../../tinytest/tinytest.h"
#include "sort.h"

void test_addition()
{
  int arry[] = {4,6,1,2};
  ASSERT_EQUALS(10, merge_sort_bottom_up(arry, 4));

}


/* test runner */
int main()
{
  RUN(test_addition);

  return TEST_REPORT();
}
