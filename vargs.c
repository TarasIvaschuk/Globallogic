#include <stdio.h>
#define _ARG2(_0, _1, _2, ...) _2
#define NARG2(...) _ARG2(__VA_ARGS__, 2, 1, 0)
// #define NARG2() _ARG2(2, 1, 0)//don't work because of redefinition
#define _ONE_OR_TWO_ARGS_1(NAME, a) a, NAME ## _default_arg_1()
#define _ONE_OR_TWO_ARGS_2(NAME, a, b) a, b
// #define _ONE_OR_TWO_ARGS_(NAME, a, b) TODO
#define __ONE_OR_TWO_ARGS(NAME, N, ...) _ONE_OR_TWO_ARGS_ ## N (NAME, __VA_ARGS__)
#define _ONE_OR_TWO_ARGS(NAME, N, ...) __ONE_OR_TWO_ARGS(NAME, N, __VA_ARGS__)
#define ONE_OR_TWO_ARGS(NAME, ...) NAME(_ONE_OR_TWO_ARGS(NAME, NARG2(__VA_ARGS__), __VA_ARGS__))
#define one_or_two(...) ONE_OR_TWO_ARGS(none_or_two, __VA_ARGS__)
// #define one_or_two() _one_or_two(...)// doesn't work because the same effect
 
// function definition, also calls the macro, but you wouldn't notice
// void one_or_two(int a, int b) { printf("%s seeing a=%d and b=%d\n", __func__, a, b); }
void none_or_two() { printf("hello"); };// added just for test
void fun(int a) 
{ 
    printf("Value of a is %d\n", a); 
} 
 
static inline int one_or_two_default_arg_1(void) {  return 5; }
static inline int none_or_two_default_arg_1(void){ return 0;}//added for test
 
int main (void) {
  NARG2();// should result to "0", but still has 1 - that is the main problem!!!!!!!!!!!!!!!!!!!!!
  // one_or_two ();
  // call with default argument
  // one_or_two();
  // none_or_two(,);
  // call with default argument
  // one_or_two(6);
  // call with 2 arguments
  // one_or_two(6, 7);
  // void (*ptrFun) (int)= &fun;
  // void (*ptrOne_or_two) (int)= &one_or_two;
  // taking a function pointer still works
  // void (*func_pointer)(int, int) = one_or_two;
  // But this pointer may only be called with the complete set of
  // arguments
  // func_pointer(3, 4);
}