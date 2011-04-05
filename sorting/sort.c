#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MIN(A,B) ((A) < (B) ? (A):(B))
int count = 0;


int insertion_sort(int* a, int size)
{
  int i,j,tmp;
  for(i=1; i<size; i++) {
    for(j=i; (j>0 && (a[j-1] > a[j])); j--) {
      tmp = a[j-1];
      a[j-1]= a[j];
      a[j] = tmp;
    }
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
    count++; //for test purposes
  }
  return 0;
}

			 
int merge_sort_bottom_up(int* arry, int size)
{
  count=0;
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
  printf("count=%d",count);
  return 0;
};





