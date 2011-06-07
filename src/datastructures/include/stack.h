#include <stdbool.h>

typedef struct Stack_Struct *Stack_T;

extern Stack_T Stack_new();
extern void Stack_dispose(Stack_T *stk_ptr);
extern bool Stack_isEmpty(Stack_T stk);
extern void Stack_push(void* val, Stack_T stack);
extern void* Stack_pop(Stack_T stack);


