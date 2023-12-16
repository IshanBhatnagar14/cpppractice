#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> 
#include <mutex>

int my_amount = 0;

std::mutex m ;

void addMoney(){
    m.lock();
    ++my_amount;
    m.unlock();
}

int main()
{
    std::thread t1(addMoney);

    std::thread t2 (addMoney);

    t1.join();
    t2.join();

    std::cout<<my_amount << std::endl;
}
