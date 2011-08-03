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
  ASSERT_EQ('c', rbTree.find(3));
}
