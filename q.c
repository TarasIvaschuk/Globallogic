#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
   //!stack=showMemory(start=65520, cursors=[q,stack])
   struct sNode *s = (struct sNode *)malloc(sizeof(struct sNode));
   printf("The address of stack at first creation is %p and the data is %d and the next is %d\n", s, s->data, s->next);
   s->next=NULL;
   push(&s, 2);
   pop(&s);
   pop(&s);
   // push(&s, 1);
   // pop(&s);
   // pop(&s);
   // printf("The address of q->stack->data is hello\n");
   // struct Queue * q= (struct Queue *)malloc (sizeof (struct Queue));
   // q->stack=NULL;
   // printf("The address of queue at first creation is %p and the stack is %p\n", q, q->stack);
//    printf("The address of q->stack->next is %d\n",*((*q).stack).data);
   // printf("The address of q->stack->data is %d\n",q->stack->data);

   // enQueue (q,1);
   // enQueue (q,2);
   // enQueue (q,3);
   // deQueue (q);
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
   printf("address of new value is %p ", new_node);
   printf("push the %d\n", new_data);
   new_node->next = (*top);
   (*top) = new_node;
}
int pop(struct sNode **top)
{
   //!heap=showMemory (start=100, cursors=[lastNode])
   if ((*top)->next == NULL)//works with stack
   // if ((*top) == NULL) //works with queue
   {
       printf("Stack underflow \n");
       return -555555;
   }
   struct sNode *lastNode = *top;
   int num = lastNode->data;
   printf("the top is %p ", *top);
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

   if (queue->stack->next == NULL)
   {
       int res=pop(&(queue->stack));
       printf ("Dequeue the %d\n",res);
       return res;
   }
   else
   {
       int x = pop(&(queue->stack));
       int temp = deQueue(queue);
       push(&(queue->stack),x);
       return temp;
   }
}


