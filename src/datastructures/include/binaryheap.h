#include "heap.h"

namespace datastructures {
template <class T>  
  class BinaryHeap : public Heap<T>  {

 public:
    BinaryHeap(int size);
    T remove();
    void insert(T& item);

  private:
    int _size;
    T* _items;
  };
}
