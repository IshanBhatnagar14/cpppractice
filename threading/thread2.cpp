#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> 

// void fun(int x) {

//     while(x --> 0){
//         std::cout << x <<std::endl;
//     }
// }

// int main(){
//     std::thread t1(fun,11);
//     t1.join();
//     return 0;
// }

// 2. Lambda Function

// int main () {

//     auto fun = [](int x) {

//      while(x --> 0){
//          std::cout << x <<std::endl;
//      }
// }

// 4.  Non static member function  5. static member function

class Base
{
    public:

    void run(int x) {
        while(x--  > 0) {

            std::cout << x << std::endl;
        }
    }
};

int main() {
    Base b;
    std::thread t(&Base::run, &b,10);   // std::thread t(&Base::run,10);  
    t.join();
    return 0;
}