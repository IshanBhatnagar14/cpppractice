# include <iostream>
# include <thread>
# include <chrono>
# include <algorithm>
# include <future>

typedef long int ull;

void findOdd(std::promise<ull> &&OddSumPromise,ull start, ull end){

    ull OddSum = 0;

    for (ull i=start; i <= end; ++i) {

        if (i & 1 ) {
            OddSum+=i;
        }
    }
    OddSumPromise.set_value(OddSum);
    
    
    }


int main() {

    ull start =0 , end =198424498 ;

    std::promise<ull> OddSum ;

    std::future<ull> OddFuture ;

    OddFuture = OddSum.get_future();

    std::thread t1 (findOdd,std::move(OddSum),start,end);

    std::cout<<"Waiting for Result" << std::endl;

    std::cout<<"OddSum :"<<OddFuture.get() <<std::endl;

    t1.join();

    return 0;
    

}