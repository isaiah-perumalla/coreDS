#include <stdbool.h>

typedef struct Stack_T *Stack_T;

Stack_T Stack_new();
void Stack_dispose(Stack_T *stk_ptr);
bool Stack_isEmpty(Stack_T stk);
void Stack_push(void* val, Stack_T stack);
void* Stack_pop(Stack_T stack);


