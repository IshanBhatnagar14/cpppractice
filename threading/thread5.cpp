#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> 
#include <mutex>

int my_amount = 0;

std::mutex m ;

void addMoney1000(){
    for (int i=0;i<100000;++i) {

        if(m.try_lock())
        ++my_amount;
        m.unlock();

    }
    
}

int main()
{
    std::thread t1(addMoney1000);

    std::thread t2 (addMoney1000);

    t1.join();
    t2.join();

    std::cout<<my_amount << std::endl;
}

