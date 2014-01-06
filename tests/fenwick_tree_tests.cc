#include "gtest/gtest.h"
#include "fentree.h"


TEST(FenwickTreeTest, QueryAndUpdate) {
  int size = 100;
  FenTree_T ftree  = FenTree_new(size);
  int i;
  for(i=1; i <= size; i++) FenTree_update(ftree, i, i);
  
  int l,r,n;
  n = 100;
  for(l=1; l < n; l++) {
    for(r=l+1; r < n; r++) {
    int sum = FenTree_get_range_sum(ftree, l,r);
    int expected = (r*(r+1)/2) - (((l-1)*l)/2);
    EXPECT_EQ(expected, sum);
    }
  }



}
