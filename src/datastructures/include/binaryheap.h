#include "heap.h"

namespace datastructures {
template <class T>  
  class BinaryHeap : public Heap<T>  {

 public:
    BinaryHeap(int size){
      _size = size;
      _items = new T[_size];
    }
    
    T remove(){return 0;}
    void insert(T& item){}

  private:
    int _size;
    T* _items;
  };
}
