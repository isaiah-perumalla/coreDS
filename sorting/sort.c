#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MIN(A,B) ((A) < (B) ? (A):(B))
#define SWAP(x,y, swap_size) do \ 
   { unsigned char swap_temp[swap_size]; \
     memcpy(swap_temp,y,swap_size); \
     memcpy(y,x, swap_size); \
     memcpy(x,swap_temp,swap_size); \
    } while(0)


static void  swap(int *a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static void compare_n_swap(int* a, int* b)
{
  if(*a > *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

int insertion_sort(int* a, int size)
{
  int i,j, key;

  for(i=size-1; i >0;i--) 
    if(a[i-1] >  a[i]) swap(&a[i-1], &a[i]);
  for(i=1; i<size; i++) {
    key = a[i];
    j=i;
    while(a[j-1] > key) {
      a[j]= a[j-1];
      j--;
    }
    a[j]=key;
  }    
  return 0;
}

int ins_sort(void* arry, int size, size_t esize, 
	     int(*compare)(const void* key1, const void* key2))
{
  char* a = (char*) arry;
  void* key = malloc(esize);
  if(key == NULL) return -1;

  int i,j;
  //find smallest element and put in position 0, serves as sentinel to tighten inner loop  
  for(i=size-1; i >0;i--) {
    void* ele_i = a+ i*esize;
    void* ele_i_minus_1 = a+(i-1)*esize;
    if(compare(ele_i_minus_1, ele_i) > 0) SWAP(ele_i, ele_i_minus_1, esize);
  }
  for(i=1; i<size; i++) {
    memcpy(key, a+i*esize, esize);// store in temp to minimize swaps and make inner loop tighter
    j=i;
    while(compare(a+(j-1)*esize, key) > 0) {
      memcpy(a+j*esize, a+(j-1)*esize, esize);
      j--;
    }
    memcpy(a+j*esize, key, esize);
  }    
  free(key);
  return 0;
}

int binary_ins_sort(void* arry, int size, size_t esize, 
			  int(*compare)(const void* key1, const void* key2))
{
  void* key = malloc(esize);
  if(key == NULL ) return -1;
  int i,j;
  char* a = (char*)arry;
  for(i=1; i<size;i++) {
    memcpy(key, a+i*esize, esize);
    if(compare(key, a+(i-1)*esize) != -1) continue; 
    j = binary_search(key,arry,i-1, esize, compare);
    if(j < 0) j = ~j;
    memmove(a+(j+1)*esize, a+j*esize, (i-j)*esize);
    memcpy(a+j*esize, key, esize);
  }
  free(key);
  return 0;
}


//basic partitioning strategy, 
//very bad O(n^2) performance on nearly ordered files


static int simple_partition(void* arry, int start_index, int end_index, size_t esize, 
			      int (*compare)(const void* key1, const void* key2))
{
  char*  start= (char*)arry;
  void* pivot = start+end_index*esize;
  for(start_index--;;) {
    while(compare(start+((++start_index)*esize), pivot) < 0);
    while(compare(start+((--end_index)*esize), pivot) > 0) if(end_index<=start_index) break;
    if(end_index <= start_index) break;
    void* left_ele = start+start_index*esize;
    void* right_ele = start+end_index*esize;
    SWAP(left_ele, right_ele, esize);
  }
  SWAP(start+start_index*esize, pivot, esize);
  return start_index;
}

static int* q_partition(int* start, int* end)
{
  assert(*(start-1) <= *end);
  int *i, *j, pivot = *end;
  j=end;
  for(i=start-1;;) {
    while(*(++i) < pivot);
    while(*(--j) > pivot);
    if(j <= i) break;
    swap(i,j);
  }
  *end = *i;
  *i = pivot;
  return i;
}

static int* median_of_3_partition(int* start, int* end)
{
  if(start >= end) return end;
  int* mid = start + (end-start)/2;
  compare_n_swap(start, mid);
  compare_n_swap(start, end);
  compare_n_swap(mid, end);
  swap(mid, end-1);
  return start+1 >= end-1 ? start : q_partition(start+1, end-1);
}


static void  hybrid_q_sort(int* start, int* end,
			   int* (*partition)(int* l, int* r))
{
  if((end - start) <= 10) return;
  int *mid = partition(start, end);
  hybrid_q_sort(start, mid-1, partition);
  hybrid_q_sort(mid+1, end, partition);
}

static void standard_qsort(void* arry, int l, int r, size_t esize,
			   int (*partition)(void* arry, int lo, int hi, size_t esize,
					    int (*compare)(const void* key1, const void* key2) ),
			  int (*compare)(const void* key1, const void* key2))
{
  if(r <= l) return;
  int mid = partition(arry, l, r, esize, compare);
  standard_qsort(arry, l, mid-1, esize, partition, compare);
  standard_qsort(arry, mid+1, r, esize, partition, compare);
}
int basic_quick_sort(void* arry, int size, size_t esize,
		     int (*compare)(const void* key1, const void* key2))
{
  standard_qsort(arry, 0, size-1, esize, simple_partition, compare);
  return 1;
}

int quick_sort(int* a, int size)
{
  hybrid_q_sort(a, a+ size-1, median_of_3_partition);
  return insertion_sort(a, size);
}

static void create_bitonic_seq_from(int* arry, int total_size, int lsize, int start_index, int buffer[])
{
  int i;
  for(i=0;i<lsize;i++) buffer[i] = arry[start_index++]; 
  for(i=total_size-1;i>=lsize;i--) buffer[i] = arry[start_index++];   
}

static int bitonic_merge(int* arry, int sindex, int mindex, int endIndex) 
{
  if(sindex >= endIndex) return 0;
  if(arry[mindex-1] <= arry[mindex]) return 0;
  int lsize, total_size;
  lsize = mindex-sindex;
  total_size = endIndex-sindex+1;
  int bitonic_arry[total_size];
  create_bitonic_seq_from(arry,total_size, lsize,sindex, bitonic_arry) ;
  int lpos, rpos,value;
  lpos =0;
  rpos = total_size-1;
  while(lpos <= rpos){
    value = (bitonic_arry[lpos] <= bitonic_arry[rpos]) ? bitonic_arry[lpos++] :bitonic_arry[rpos--];
    arry[sindex++] = value;
  }
  return 0;
}

/*
merge sort with optimizations
switches to insertion sort for small, sub arrays
worst case running time of insertion sort n(n-1)/2 -n 

int optimized_merge_sort_bottom_up(int* arry, int size)
{
  
}
*/			 
int merge_sort_bottom_up(int* arry, int size)
{
  int start, mid, end, block_size =1;
  while(block_size < size) {
    start =0;
    while(start < size){
      mid = MIN(size-1,start+block_size);
      end = MIN(size-1,start+(block_size<<1)-1);
      bitonic_merge(arry, start,mid,end);
      start = end+1;
    }
    block_size <<= 1;
  }
  return 0;
};

int binary_search(const void* ele, void* arry, int size, size_t esize,
		  int (*compare)(const void* a, const void* b))
{
  char* start = (char*)arry;
  int hi, lo;
  hi = size-1;
  lo = 0;
  while(lo <= hi) {
    int mid = lo + ((hi-lo)>>1);
    int cmp = compare(ele, start+mid*esize);
    if(cmp == 1) lo = mid+1;
    if(cmp == 0) return mid;
    else hi = mid-1;
  }
return -1*(lo+1);
}


int find_k_smallest_linear(int k, int* a1, int size1, int* a2, int size2)
{
  return 0;
}



