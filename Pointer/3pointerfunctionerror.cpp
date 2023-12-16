# include<stdio.h>
# include<stdlib.h>

void printhelloworld() {
    printf("Hello World\n");
}
int *Add(int* a,int* b) {
    int c = (*a) + (*b);

    return &c ;
}

int main() {
    int a = 2 ,b=4;
    
    int *ptr = Add(&a,&b);
    printhelloworld();
    printf("Sum =%d\n",*ptr); // concept of stack called function , we can solve this error , by memory allocation on heap.
}