#include "gtest/gtest.h"
#include "heap.h"
#include "binaryheap.h"
#include <functional>


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

struct Compare_int_ptr {
  int operator()(const int* ptr1, const int* ptr2) {
    if(*ptr1 > *ptr2) return 1;
    else if (*ptr1 == *ptr2) return 0;
    else return -1;
  }
};

TEST_F(BinaryHeapTest, HeapInsertRemove) {
  datastructures::BinaryHeap<int, std::greater<int> > heap(10);
  //  datastructures::BinaryHeap<int, Compare_int_ptr > heap1(10);
  int x1, x2, x3;
  x1 = 5;
  x2 = 2;
  x3 = 3;
  heap.insert(x1);
  heap.insert(x2);
  heap.insert(x3);
  ASSERT_EQ(heap.remove(), x2);
}
