#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "mem.h"
#include "assert.h"

#define PARENT(i) ((i-1) >> 1)
#define LEFT(i) (((i+1) << 1) -1)
#define RIGHT(i) ((i+1) << 1) 

struct Heap_T {
  int index;
  int size;
  heap_type type;
  compare_fn compare;
  void** array;
};


static void  heapify_up(Heap_T heap, int index)
{
  int i;
  for(i=index; i >=1; i = PARENT(i)) {
    if(heap->compare(heap->array[i], heap->array[PARENT(i)]) != heap->type) break;
   
    SWAP(&heap->array[i] , &heap->array[PARENT(i)], sizeof(void*));
  }
}

static void heapify_down(Heap_T heap, int index)
{
  assert(index >= 0 );
  int i, top_index;
  for(i=index; i< heap->index && LEFT(i) < heap->index; ) {
    
    top_index =heap->compare(heap->array[i], heap->array[LEFT(i)]) == heap->type ? i : LEFT(i);
    if(RIGHT(i) < heap->index)
      top_index = heap->compare(heap->array[top_index], heap->array[RIGHT(i)]) == heap->type ? top_index : RIGHT(i);
    if(top_index == i) break;

    SWAP(&heap->array[i], &heap->array[top_index], sizeof(void*));
    i = top_index;
  }
    
}

Heap_T Heap_new(int size, heap_type type, compare_fn compare)
{
  Heap_T heap;
  NEW(heap);
  heap->index = 0;
  heap->size = size+1;
  heap->type = type;
  heap->compare = compare;
  heap->array = malloc(sizeof(*(heap->array)) * heap->size);
  return heap;
}

void Heap_insert(void* val, Heap_T heap)
{
  assert(heap->index < heap->size );
  heap->array[heap->index] = val;
  heapify_up(heap, heap->index++);
}
void* Heap_remove(Heap_T heap)
{
  assert(heap->index > 0);
  void* val = heap->array[0];
  heap->array[0] = heap->array[--heap->index];
  heapify_down(heap, 0);
  return val;
}

