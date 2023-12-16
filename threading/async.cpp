#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>
typedef long int ull;

ull findOdd(ull start, ull end) {
    std::cout << "Thread Id for func " << std::this_thread::get_id() <<std::endl;
    
    ull OddSum = 0;
    for (ull i =start; i <= end; ++i){
        if (i & 1){
            OddSum+=i;
        }
    }
    return OddSum;
}

int main() {

    ull start = 0 , end = 192325;

    std::cout << "Thread Id for Main " << std::this_thread::get_id() <<std::endl;

    std::cout<<" Thread created if policy is std::launch::async"<<std::endl;

    std::future<ull> OddSum = std::async(std::launch::async,findOdd,start,end);

    std::cout<<OddSum.get()<<std::endl;

    return 0;

}