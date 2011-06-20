#include "gtest/gtest.h"
#include "heap.h"
#include "binaryheap.h"
#include <functional>


class BinaryHeapTest : public testing::Test {
 protected:
  virtual void SetUp() {

  }

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

TEST_F(BinaryHeapTest, HeapNoRightChildInsertRemove) {
    datastructures::BinaryHeap<int> heap(3);
    int x1 = 41;
    int x2 = 3;
    int x3 = 10;
    heap.insert(x1);
    heap.insert(x2);
    heap.insert(x3);
    
    heap.remove();
    ASSERT_EQ(10, heap.top());
    
}

TEST_F(BinaryHeapTest, HeapInsertRemove) {
  datastructures::BinaryHeap<int> heap(10);
  //  datastructures::BinaryHeap<int, Compare_int_ptr > heap1(10);
  int x1, x2, x3, x7;
  x1 = 5;
  x2 = 2;
  x7 = 7;
  x3 = 3;
  heap.insert(x1);
  heap.insert(x2);
  heap.insert(x7);
  heap.insert(x3);  
  ASSERT_EQ(x2, heap.top());
  heap.remove();

  ASSERT_EQ(x3, heap.top());
}

TEST_F(BinaryHeapTest, HeapInsertRemoveOnLargeInput) {
  int size = 1001;
  datastructures::BinaryHeap<int> heap(size);
  for(int i =size; i > 0; i--)  heap.insert(i);
  
  for(int i=1; i<=size; i++) {
    ASSERT_EQ(i, heap.top());
    heap.remove();
  }
}
