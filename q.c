#include <stdio.h>
#include <stdlib.h>

/* Implementation of queue via stack+recursion
details see https://www.geeksforgeeks.org/queue-data-structure/
Implemented add to queue and stack with default value of 1 
by means of macro */

#define Push(stack,...)  push(stack,(((sizeof((int[])\
{0, ##__VA_ARGS__})/sizeof(int)-1)==0)? 1:__VA_ARGS__##0/10))

#define EnQueue(queue,...)  enQueue(queue,(((sizeof((int[])\
{0, ##__VA_ARGS__})/sizeof(int)-1)==0)? 1:__VA_ARGS__##0/10))

struct sNode
{
   int data;
   struct sNode *next;
};
struct Queue
{
   struct sNode *stack;
};

void push(struct sNode **top, int new_data);
int pop(struct sNode **top);
void enQueue(struct Queue *queue, int data);
int deQueue(struct Queue *queue);
struct sNode *createStack();
struct Queue *createQueue();

int main(void)
{
   //!stack=showMemory(start=65520, cursors=[q,stack])
   struct sNode *s =createStack ();
   printf("The address of stack at first creation is %p and the data is %d and the next is %p\n", s, s->data, s->next);
   Push(&s);
   pop(&s);
   pop(&s);
   struct Queue *q =createQueue ();
   printf("The address of queue is %p, stack is %p, the stack data is %d, the stack next is %p\n", q, q->stack, q->stack->data, q->stack->next);
   EnQueue (q);//again
   deQueue (q);
   deQueue (q);
   return 0;
}
void push(struct sNode **top, int new_data)
{
   //!heap=showMemory(start=100, cursors=[new_node])
   struct sNode *new_node = (struct sNode *)malloc(sizeof(struct sNode));
   if (new_node == NULL)
   {
      printf("Stack overflow \n");
      return;
   }
   new_node->data = new_data;
   printf("address of new value is %p\n ", new_node);
   printf("Push the %d\n", new_data);
   new_node->next = (*top);
   (*top) = new_node;
}
int pop(struct sNode **top)
{
   //!heap=showMemory (start=100, cursors=[lastNode])
   if ((*top)->next == NULL) //works with stack
   // if ((*top) == NULL) //works with queue
   {
      printf("Stack underflow \n");
      return -555555;
   }
   struct sNode *lastNode = *top;
   int num = lastNode->data;
   printf("the top is %p\n ", *top);
   (*top) = lastNode->next;
   free(lastNode);
   printf("pop the %d\n", num);
   return num;
}
void enQueue(struct Queue *queue, int value)
{
   push(&(queue->stack), value);
}
int deQueue(struct Queue *queue)
{
   if (queue->stack->next == NULL) { 
        printf("Q is empty\n"); 
        getchar(); 
        exit(0); 
    } 

   if (queue->stack->next->next == NULL)
   {
      int res = pop(&(queue->stack));
      printf("Dequeue the %d\n", res);
      return res;
   }
   else
   {
      int x = pop(&(queue->stack));
      int temp = deQueue(queue);
      push(&(queue->stack), x);
      return temp;
   }
}
struct sNode *createStack()
{
   struct sNode *new_node = (struct sNode *)malloc(sizeof(struct sNode));
   new_node->data = 0;
   new_node->next = NULL;
   return new_node;
}
struct Queue *createQueue()
{
   struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
   struct sNode *s = createStack();
   q->stack = s;
   return q;
}
