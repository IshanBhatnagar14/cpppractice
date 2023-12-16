#include<stdio.h>
void Increment(int *p)
{
    *p = *p + 1 ;
}
int main()
{
    int a ;
    a = 10;
    Increment(&a);
    printf("a = %d",a);
}