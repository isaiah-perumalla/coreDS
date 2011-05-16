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



static void compare_n_swap(void* a, void* b, size_t esize, compare_fn compare)
{
  if(compare(a, b) > 0) {
    SWAP(a, b, esize);
  }
}


int ins_sort(void* arry, int size, size_t esize, compare_fn compare)
{
  char* a = (char*) arry;
  unsigned char key[esize]; //allocate to store key
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
  return 0;
}

int binary_ins_sort(void* arry, int size, size_t esize, compare_fn compare)
{
  int i,j;
  unsigned char key[esize];
  char* a = (char*)arry;
  for(i=1; i<size;i++) {
    memcpy(key, a+i*esize, esize);
    if(compare(key, a+(i-1)*esize) != -1) continue; 
    j = binary_search(key,arry,i-1, esize, compare);
    if(j < 0) j = ~j;
    memmove(a+(j+1)*esize, a+j*esize, (i-j)*esize);
    memcpy(a+j*esize, key, esize);
  }
  return 0;
}


//basic partitioning strategy, 
//very bad O(n^2) performance on nearly ordered files


static int simple_partition(void* arry, int start_index, int end_index, size_t esize, 
			    compare_fn compare)
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

static int q_partition(void* arry, int l_index, int r_index, size_t esize, compare_fn compare)
{
  char* start = (char*)arry;
  assert(compare(start+(l_index-1)*esize, start+r_index*esize) < 0 );
  void* pivot = start+r_index*esize;
  int i,j;
  j = r_index;
  for(i=l_index-1;;) {
    while(compare(start+((++i)*esize), pivot) < 0);
    while(compare(start+((--j)*esize), pivot) > 0);
    if(j <= i) break;
    SWAP(start+i*esize,start+j*esize, esize);
  }
  SWAP(start+i*esize, pivot, esize);
  return i;
}

static int median_of_3_partition(void* arry, int start_index, int end_index, size_t esize, 
				 compare_fn compare)
{
  char* start = (char*)arry;
  if(start_index >= end_index) return end_index;
  int mid = start_index + ((end_index-start_index)>>1);
  compare_n_swap(start+start_index*esize, start+mid*esize, esize, compare);
  compare_n_swap(start+start_index*esize, start+end_index*esize, esize, compare);
  compare_n_swap(start+mid*esize, start+end_index*esize, esize, compare);
  SWAP(start+mid*esize, start+(end_index-1)*esize, esize);
  return start_index+1 >= end_index-1  ? start_index : q_partition(arry, start_index+1, end_index-1, esize, compare);
}


static void  hybrid_q_sort(void* arry, int start_index, int end_index, size_t esize,
			   int (*partition)(void* arry, int lo, int hi, size_t esize,
					    compare_fn compare),
			   compare_fn compare)
{

  if((end_index - start_index) <= 10) return;
  int mid = partition(arry, start_index, end_index,esize, compare);
  hybrid_q_sort(arry, start_index, mid-1, esize, partition, compare);
  hybrid_q_sort(arry,mid+1, end_index, esize, partition, compare);
}

static void standard_qsort(void* arry, int l, int r, size_t esize,
			   int (*partition)(void* arry, int lo, int hi, size_t esize,
					    compare_fn compare),
			   compare_fn compare)
{
  if(r <= l) return;
  int mid = partition(arry, l, r, esize, compare);
  standard_qsort(arry, l, mid-1, esize, partition, compare);
  standard_qsort(arry, mid+1, r, esize, partition, compare);
}
int basic_quick_sort(void* arry, int size, size_t esize, compare_fn compare)
{
  standard_qsort(arry, 0, size-1, esize, simple_partition, compare);
  return 1;
}

int quick_sort(void* arry, int size, size_t esize, compare_fn compare)


{
  hybrid_q_sort(arry,0,size-1, esize, median_of_3_partition, compare);
  return ins_sort(arry, size, esize, compare);
}

static void bitonic_seq_on(char buffer[], char* a, int sindex, int mindex, int endindex, size_t esize)
{
  int i,j;
  for(i=sindex, j=0; i< mindex;i++, j++) memcpy(buffer+j*esize, a+i*esize, esize); 
  for(i=endindex; i>=mindex;i--, j++) memcpy(buffer+j*esize, a+i*esize, esize); 
}

static int bitonic_merge(void* a, int sindex, int mindex, int endIndex, size_t esize, compare_fn compare) 
{
  if(sindex >= endIndex) return 0;
  char* arry = (char*)a;
  if(compare(arry+(mindex-1)*esize,  arry+mindex*esize) < 0) return 0;
  int total_size = endIndex-sindex+1;
  char  buffer[total_size*esize];
  bitonic_seq_on(buffer, arry, sindex, mindex, endIndex, esize);
    
  int lpos, rpos = total_size-1;
  for(lpos=0;sindex <= endIndex;sindex++) {
    if(compare(buffer+lpos*esize, buffer+rpos*esize) < 1) {
      memcpy(arry+sindex*esize, buffer+lpos*esize, esize);
      lpos++;
    }
    else {
      memcpy(arry+sindex*esize, buffer+rpos*esize, esize);
      rpos--;
    }
  }
  return 0;
}

int static td_merge_sort(void* arry, int sindex, int endindex, size_t esize, compare_fn compare)
{
  if(endindex <= sindex) return 0;
  int mid = sindex + ((endindex - sindex) >> 1);
  //invariant mid >= sindex , endindex > mid, 
  //for this reason sort seq{sindex ... mid}, seq{mid+1 ... endindex}
  td_merge_sort(arry, sindex, mid, esize, compare);
  td_merge_sort(arry, mid+1, endindex, esize, compare);
  return bitonic_merge(arry, sindex, mid+1, endindex, esize, compare);
}

int merge_sort_top_down(void*  arry, int size, size_t esize, compare_fn compare)
{
  return td_merge_sort(arry, 0, size-1, esize, compare);
}

int merge_sort_bottom_up(void* arry, int size, size_t esize, compare_fn compare)
{
  int start, mid, end, block_size =1;
  while(block_size < size) {
    start =0;
    while(start < size){
      mid = MIN(size-1,start+block_size);
      end = MIN(size-1,start+(block_size<<1)-1);
      bitonic_merge(arry, start,mid,end, esize, compare);
      start = end+1;
    }
    block_size <<= 1;
  }
  return 0;
};

int binary_search(const void* ele, void* arry, int size, size_t esize,
		  compare_fn compare)
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



