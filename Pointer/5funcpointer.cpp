# include<stdio.h>
int Add(int a, int b)
{
    return a+b;
}
int main()
{
    int c;

    int (*p)(int,int);  // Function Pointer
    p = &Add;
    c = (*p)(2,3);
    printf("%d",c);
}