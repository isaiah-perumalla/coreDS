#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MIN(A,B) ((A) < (B) ? (A):(B))

int insertion_sort(int* a, int size)
{
  int i,j,key;
  for(i=1; i<size; i++) {
    key = a[i];// store in temp to minimize swaps and make inner loop tighter
    for(j=i; (j>0 && (a[j-1] > key)); j--) {
      a[j]= a[j-1];
    }
    a[j]=key;
  }    
  return 0;
}

int binary_insertion_sort(int* a, int size)
{
  int i,j, key;
  for(i=1; i<size;i++) {
    key = a[i];
    if(key >= a[i-1]) continue; 
    j = b_search(key,a,i-1);
    if(j < 0) j = ~j;
    memmove(a+j+1, a+j, sizeof(int)*(i-j));
    a[j]= key;
  }
  return 0;
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

int b_search(int ele, int* arr, int size)
{
  int i,mid,hi = size-1;
  for(i=0;i<=hi;) { 
    mid = i+ ((hi-i)>>1);
    if(arr[mid] == ele) return mid;
    if(arr[mid] < ele) 
      i = mid+1;
    else
      hi = mid-1;
  }
  return -1*(i+1);
}




