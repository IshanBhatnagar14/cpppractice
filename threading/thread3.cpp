#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> 

void run (int count) {

    while(count-- > 0 )
      std::cout<<"CPPNuts" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main() {

    std::thread t1(run,10);
    std::cout << "main()" << std::endl;

    
    if(t1.joinable())
    t1.join(); // t1.detach();


    std::cout<<"main() after"<< std::endl;
}