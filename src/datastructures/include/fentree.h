
typedef struct FenTree_Struct *FenTree_T;

extern FenTree_T FenTree_new(int n);
extern void FenTree_dispose(FenTree_T *ptrFenTree);
extern int  FenTree_get_range_sum(FenTree_T ftree, int i, int j);
extern void FenTree_update(FenTree_T ftree, int i, int val);

