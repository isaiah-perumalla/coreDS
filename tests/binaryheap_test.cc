#include "gtest/gtest.h"
#include "heap.h"
#include "binaryheap.h"

class BinaryHeapTest : public testing::Test {
 protected:
  // Remember that SetUp() is run immediately before a test starts.
  // This is a good place to record the start time.
  virtual void SetUp() {

  }

  // TearDown() is invoked immediately after a test finishes.  Here we
  // check if the test was too slow.
  virtual void TearDown() {

  }

};

TEST_F(BinaryHeapTest, HeapInsertRemove) {
  datastructures::BinaryHeap<int> heap(10);
  int x1, x2, x3;
  x1 = 5;
  x2 = 2;
  x3 = 3;
  heap.insert(x1);
  heap.insert(x2);
  heap.insert(x3);
  ASSERT_EQ(heap.remove(), x2);
}
