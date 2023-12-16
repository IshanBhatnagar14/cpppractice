#include<iostream>

template<class T1, class T2>

float funcavg(T1 a, T2 b){
    float avg = (a+b)/2;
    return avg;
}

int main(){
    float a;
    a = funcavg(5,2.3);

    printf("the average is %.3f",a);

    return 0;
}