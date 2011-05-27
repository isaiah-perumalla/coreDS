#include <stdbool.h>
#include<stdlib.h>

typedef struct Stack_T *Stack_T;

Stack_T Stack_new();
bool Stack_isEmpty(Stack_T stk);
void Stack_push(void* val, Stack_T stk);
void* Stack_pop(Stack_T stk);
void Stack_dispose(Stack_T *stk);
