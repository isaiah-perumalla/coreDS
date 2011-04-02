#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MIN(A,B) ((A) < (B) ? (A):(B))
int count = 0;
int merge(int* arry, int sindex, int mindex, int endIndex) {

  if(sindex >= endIndex) return 0;

  if(arry[mindex-1] <= arry[mindex]) return 0;
  int lsize,rsize;
  lsize = mindex-sindex;
  rsize = endIndex-mindex+1;

  int* left_arry = (int*)malloc((lsize)*sizeof(int));
  int* right_arry = (int*)malloc((rsize)*sizeof(int));
  if(left_arry ==0 || right_arry == 0) return -1;
  int lpos, rpos,i;
  lpos = rpos =0;
  i = sindex;
  while(lpos < lsize)  left_arry[lpos++]=arry[i++];

  while(rpos < rsize) right_arry[rpos++]=arry[mindex++];
  

  i = sindex;
  lpos = rpos =0;
  while(lpos < lsize && rpos < rsize){
    if(left_arry[lpos] <= right_arry[rpos])
      arry[i++] = left_arry[lpos++];
    else 
      arry[i++] = right_arry[rpos++];
    count++;
  }

  if(lpos<lsize)
    memcpy(&arry[i], &left_arry[lpos], (lsize-lpos)*sizeof(int));
  else
    memcpy(&arry[i], &right_arry[rpos], (rsize-rpos)*sizeof(int));
  free(left_arry);
  free(right_arry);
  return 0;
}

int merge_sort_bottom_up(int* arry, int size)
{
  count=0;
  int block_size =1;
  while(block_size < size) {
    int start =0;
    while(start < size){
      int mid = MIN(size-1,start+block_size);
      int end = MIN(size-1,start+(block_size<<1)-1);

      merge(arry, start,mid,end);
      start = end+1;
    }
    block_size <<= 1;

  }
  printf("count=%d",count);
  return 0;
};





