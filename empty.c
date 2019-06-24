#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

// #define       NUMARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)
// #define       SUM(...)  sum(NUMARGS(__VA_ARGS__), ##__VA_ARGS__)
// #define       Test(...)  test((sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1),##__VA_ARGS__)
#define __push_2(stack,...) push (2,stack,__VA_ARGS__)
#define __push_1(stack,...) push (2,__VA_ARGS__,1)
#define _push(count,stack,...) __push_ ## count (stack,##__VA_ARGS__)
#define Push(stack,...)  push(stack,(((sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)==0)? 1:__VA_ARGS__##0/10))
struct sNode
{
   int data;
   struct sNode *next;
};
struct sNode *createStack();

void push(struct sNode **top,int new_data);
// void push_1(int args,...) {return 1;};
// void test (int args,...){ 
//     printf ("Hello");
// }

// void sum(int numargs, ...);

int main() {
    // printf("%d",2>3? 3:8);
    // Test ();
    struct sNode *s =createStack ();
//    printf ("%d\n",(sizeof((int[]){0})/sizeof(int)-1)==0);
     Push(&s,36);
    //   push(&s,( 3>4? 1:4 ));
    // SUM();
    // SUM(1, 2);
    // SUM(1, 2, 3);
    // SUM(1, 2, 3, 4);
    return 0;
}

// void sum(int numargs, ...) {
//     int total = 0;
//     va_list ap;

//     printf("sum() called with %d params:", numargs);
//     va_start(ap, numargs);
//     while (numargs--)
//         total += va_arg(ap, int);
//     va_end(ap);
//     printf(" %d\n", total);
//     return;
// }

void sum(int numargs, ...) {
    int total = 0;
    va_list ap;

    printf("sum() called with %d params:", numargs);
    va_start(ap, numargs);
    while (numargs--)
        total += va_arg(ap, int);
    va_end(ap);
    printf(" %d\n", total);
    return;
}

struct sNode *createStack()
{
   struct sNode *new_node = (struct sNode *)malloc(sizeof(struct sNode));
   new_node->data = 0;
   new_node->next = NULL;
   return new_node;
}

void push(struct sNode **top,int new_data)
{
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

};