# include<stdio.h>
# include<stdlib.h>
int *Add(int* a,int* b) {
    int c = (*a) + (*b);

    return &c ;
}

int main() {
    int a = 2 ,b=4;
    printf("Address of A in main = %d\n",&a);
    int *ptr = Add(&a,&b);
    printf("Sum =%d\n",*ptr);
}