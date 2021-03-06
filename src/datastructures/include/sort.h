#include<stdlib.h>

typedef int (*compare_fn)(const void* key1, const void* key2);
typedef int (*sort_fn)(void* a, int size, size_t esize, compare_fn compare);

int ins_sort(void* a, int size, size_t esize, compare_fn compare);

int binary_ins_sort(void* a, int size, size_t esize, compare_fn compare);

int merge_sort_bottom_up(void* arry, int size, size_t esize, compare_fn compare);
int merge_sort_top_down(void* arry, int size, size_t esize, compare_fn compare);
int merge_sort_optimized(void* arry, int size, size_t esize, compare_fn compare);
int merge_sort_optimized_bitonic(void* arry, int size, size_t esize, compare_fn compare);

int basic_quick_sort(void* arry, int size, size_t esize, compare_fn compare);
int quick_sort(void* arry, int size, size_t esize, compare_fn compare);

void  merge(void* dest, void* source, int sindex, int mid, int endindex, size_t esize, compare_fn compare);
int binary_search(const void* ele, void* arr, int size, size_t esize, compare_fn compare);
int find_k_smallest_linear(int k, int* a1, int size1, int* a2, int size2);
