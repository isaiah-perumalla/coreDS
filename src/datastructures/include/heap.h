#ifndef HEAP_INCLUDED
#define HEAP_INCLUDED

typedef int (*compare_fn)(const void* a, const void* b);
typedef struct Heap_Struct *Heap_T;
typedef int heap_type;

#define MAX_HEAP 1
#define MIN_HEAP -1

extern Heap_T Heap_new(int size, heap_type type, compare_fn compare);
extern void Heap_dispose(Heap_T *heap);
extern void Heap_insert(void* val, Heap_T heap);
extern void* Heap_remove(Heap_T heap);


namespace datastructures {
template <class T>  // E is the element type
class Heap  {

 public:
  virtual ~Heap(){};
  virtual T remove()=0;
  virtual void insert(T& item)=0; 
 };
}

#endif
