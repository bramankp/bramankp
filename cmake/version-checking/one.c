#include <stdio.h>
extern void two(void);
extern void three(void);
int main()
{
    puts("Hello, World!");
    two();
    three();
}
