/* Can be used to demonstrate redirection of stdin and stdout.
example redirect < INPUT.TXT > OUTPUT.TXT */

#include <stdio.h>

int main(void)
{
    char buf[80];

    gets(buf);
 printf("The input was: %s\n", buf);
 return 0;
}