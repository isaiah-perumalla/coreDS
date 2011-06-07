#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"

typedef  struct Stack_Node {
    void *value;
    struct Stack_Node *next;
  } Stack_Node;


typedef struct Stack_Struct {
  int count;
  Stack_Node *head;
} Stack_Struct;

//test
Stack_T Stack_new()
{
  Stack_T stk =  NEW_INSTANCE(Stack_Struct);
  stk->count = 0;
  stk->head = NULL;
  return stk;
}

bool Stack_isEmpty(Stack_T stk)
{
  return stk->count == 0;
}

void Stack_push(void* val, Stack_T stack)
{
  Stack_Node *node = NEW_INSTANCE(Stack_Node);
  node->value = val;
  node->next = stack->head;
  stack->head = node;
  stack->count++;
}

void* Stack_pop(Stack_T stack)
{
  struct Stack_Node *head = stack->head;
  void* val = NULL;
  if(head != NULL) {
    val = head->value;
    stack->head = head->next;
    FREE(head);
    stack->count--;
  }
  return val;
}

void Stack_dispose(Stack_T *stack)
{
  struct Stack_Node *current_node = (*stack)->head;
  while(current_node) {
    struct Stack_Node* next = current_node->next;
    FREE(current_node);
    current_node = next;
    }
  FREE((*stack));
  *stack = NULL;
}
   

