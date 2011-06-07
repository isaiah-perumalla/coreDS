
#define MIN(A,B) ((A) < (B) ? (A):(B))
#define SWAP(x,y, swap_size) do \
   { unsigned char swap_temp[swap_size]; \
     memcpy(swap_temp,y,swap_size); \
     memcpy(y,x, swap_size); \
     memcpy(x,swap_temp,swap_size); \
    } while(0)


#define NEW_INSTANCE(t)  (t*)malloc(sizeof(t))
#define FREE(p) free((p)), (p) = NULL
