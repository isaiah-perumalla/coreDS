#include "gtest/gtest.h"
#include "leftleaningRBTree.h"
#include <functional>
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
