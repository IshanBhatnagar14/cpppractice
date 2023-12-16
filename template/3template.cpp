#include<iostream>

template<class T1=int,class T2=float>

class Ishan {
    public:
       T1 a;
       T2 b;

       Ishan(T1 x , T2 y){
           a = x;
           b = y;
       }

       void display() {

           std::cout<<"The value of a is "<<a<<std::endl;

           std::cout<<"The value of b is "<<b<<std::endl;

       }

    
};

int main(){

    Ishan<> obj(1,3.2);
    obj.display();
    return 0;
}