#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> 

typedef unsigned long long ull ;

ull OddSum = 0;

ull EvenSum = 0;

void findEven(ull start, ull end){

    for(ull i =start;i <=end;++i){
        if ((i & 1) ==0) {
            EvenSum += i ; 
        }
    }
}

void findOdd(ull start,ull end){
    for (ull i=start;i<= end; ++i){
        if ((i & 1) == 1){
            OddSum += i;
        }
    }
}
int main () {

    ull start = 0, end = 195743 ;

    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread t1(findEven,start,end);

    std::thread t2(findOdd,start,end);

    t1.join();

    t2.join();


    // findOdd(start,end);

    // findEven(start,end);

    auto stopTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    std::cout<<"OddSum :"<<OddSum << std::endl ;

    std::cout <<"EvenSum : "<<EvenSum << std::endl ;

    std::cout<< duration.count()/1000000 << std::endl;

    return 0;
}