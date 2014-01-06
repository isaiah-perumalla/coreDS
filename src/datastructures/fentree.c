#include "fentree.h"
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"


typedef struct FenTree_Struct {
  int size, *items;
} FenTree_Struct;


FenTree_T FenTree_new(int n)
{
  FenTree_T ftree  =  NEW_INSTANCE(FenTree_Struct);
  ftree->size = n+1;
  ftree->items = (int*)calloc((n+1),sizeof(int));
  return ftree;
}


void FenTree_dispose(FenTree_T *ptrFenTree_T)
{
  FREE((*ptrFenTree_T)->items);
  FREE(*ptrFenTree_T);
}



//calcualte sum of range [1,r]
static int calculate_sum(FenTree_T ftree, int r) {
  int sum = 0;
  while(r > 0) {
    sum += ftree->items[r];
    r = r - (r & -r);
  }
  return sum;
}

int  FenTree_get_range_sum(FenTree_T fenTree, int i, int j) {
  
  if(i == 1)
    return calculate_sum(fenTree, j);
  else
    return calculate_sum(fenTree, j) - calculate_sum(fenTree, i-1);
}

void FenTree_update(FenTree_T ftree, int i, int val) {
  int maxVal = ftree->size;
  while(i < maxVal) {
    ftree->items[i] += val;
    i = i + (i & -i);
  }
}
