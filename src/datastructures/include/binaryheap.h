#include "heap.h"
#include "assert.h"
#include <functional>
namespace datastructures {
  template <typename T, typename Compare_fn = std::less<T> >  
  class BinaryHeap  {

 public:
    BinaryHeap(int size) {
      _size = size;
      _current =0;
      _items = new T[_size];
    };
    
   BinaryHeap(int size, Compare_fn &comp_fn) : BinaryHeap(size) {
      _compare_fn = comp_fn;
    };
    T remove(){
      assert(_current > 0);
      T item = _items[0];
      _items[0] = _items[--_current];
      heapify_down(0);
      return item;
    };

    void insert(T& item){
      assert(_current < _size);
      _items[_current] = item;
      heapify_up(_current++);
    };


  private:
    void heapify_up(int index) {
      //  for(int i = index; i > 0; i = parent(i)) {
      //    if(_items[i] 
    };


    void heapify_down(int index) {
      
  
    };
    Compare_fn _compare_fn;
    int _size, _current;
    T* _items;
  };
}
