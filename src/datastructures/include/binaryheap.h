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

  T top() const {
    assert(_current > 0);
    return _items[0];
  };

  void remove(){
      assert(_current > 0);
      _items[0] = _items[--_current];
      heapify_down(0);
  };

  void insert(T& item){
    assert(_current < _size);
    _items[_current] = item;
    heapify_up(_current++);
  };


  private:
  int inline parent(int i) {return (i-1) >>1;};
  int inline left(int i) {return right(i)-1;};
  int inline right(int i) {return (i+1) << 1;};
  bool inline hasLeftChild(int i) { return left(i) < _current;};

  void inline swap(int a, int b) {
    T temp = _items[a];
    _items[a] = _items[b];
    _items[b] = temp;
  };
  
  void heapify_up(int index) {
    for(int i = index; i > 0; i = parent(i)) {
      if(_compare_fn(_items[i], _items[parent(i)]))
	swap(i, parent(i));
      else break;
    }
  };


  void heapify_down(int index) {
    int max = index;
    for(int i=index; hasLeftChild(i); ) {
      if(_compare_fn(_items[left(i)], _items[max])) max = left(i);
      int r_child = right(i);
      if(r_child < _current && _compare_fn(_items[r_child], _items[max])) max = r_child;
      if(i == max) break;

      swap(i, max);
      i = max;
    }
  };

  Compare_fn _compare_fn;
  int _size, _current;
  T* _items;
  };
}
