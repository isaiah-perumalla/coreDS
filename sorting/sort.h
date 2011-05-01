#include<stdlib.h>

int ins_sort(void* a, int size, size_t esize, 
	     int (*compare)(const void* key1, const void* key2));
int binary_ins_sort(void* a, int size, size_t esize, 
	     int (*compare)(const void* key1, const void* key2));

int merge_sort_bottom_up(int* arry, int size);

int basic_quick_sort(int* arry, int size);
int quick_sort(int* arry, int size);

int b_search(int ele, int* arr, int size);
int binary_search(void* ele, void* arr, int size, size_t esize, 
		  int (*compare)(const void* key1, const void* key2));
int find_k_smallest_linear(int k, int* a1, int size1, int* a2, int size2);
