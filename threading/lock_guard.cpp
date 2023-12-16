# include <iostream>
# include <thread>
# include <mutex>

std::mutex m1 ;
int buffer = 0;

void task (const char* threadNumber, int LoopFor){

    std::lock_guard<std::mutex> lock(m1);                // Wrapper for owning mutex on scoped basis.

    for(int i=0; i <LoopFor;++i){
        buffer++;
        std::cout<<threadNumber<<buffer<<std::endl;
    }

}

int main(){
    std::thread t1(task,"T0",10);
    std::thread t2(task,"T1",10);
    t1.join();
    t2.join();
}


