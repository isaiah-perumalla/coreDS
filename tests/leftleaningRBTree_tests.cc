#include "gtest/gtest.h"
#include "leftleaningRBTree.h"
#include <functional>
#include <cmath>
using namespace datastructures;

class LeftLeaningRBTreeTest : public testing::Test {
 protected:
  virtual void SetUp() {

  }

  virtual void TearDown() {

  }

};


TEST_F(LeftLeaningRBTreeTest, InsertAndRetrieve) {
  LLRBTree<int, char> rbTree;
  rbTree.insert(1, 'a');
  rbTree.insert(2, 'b');
  rbTree.insert(3, 'c');
  ASSERT_EQ('a', *rbTree.find(1));
  ASSERT_EQ('b', *rbTree.find(2));
  ASSERT_EQ('c', *rbTree.find(3));
  rbTree.assert_LLRBInvariants();
}

TEST_F(LeftLeaningRBTreeTest, ShouldRemainBalancedForLargeSortedInput) {
  LLRBTree<int, int> rbTree;
  const int size = 1000000;
  for(int i = 0; i < size; i++) rbTree.insert(i,i);
  
  for(int i = 0; i < size; i++) ASSERT_EQ(i, *rbTree.find(i));
  int black_height = rbTree.assert_LLRBInvariants();
  ASSERT_LT(black_height , log2(size));
  std::cout <<"black height = " << black_height << std::endl;
}
