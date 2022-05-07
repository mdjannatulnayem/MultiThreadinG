#include <chrono>
#include <thread>
#include <iostream>
#include <future>

typedef unsigned long long ull;

void findOdd(std::promise<ull>&& oddSumPromise,ull start,ull end){
    ull oddSum = 0;
    for(ull i=start;i<=end;i++){
        if(i & 1){
            oddSum += i;
        }
    }
    oddSumPromise.set_value(oddSum);
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    ull start = 0, end = 1900000000;
    std::promise<ull> oddPromise; //promise object
    std::future<ull> oddFuture = oddPromise.get_future();
    std::cout << "Thread created." << std::endl;
    std::thread t1(findOdd,std::move(oddPromise),start,end);
    std::cout << "Waiting for result!!!" << std::endl;
    //assume thousand lines of code 😴 in between...!
    std::cout << "Odd sum: " << oddFuture.get() << std::endl;
    std::cout << "Completed!" << std::endl;
    if(t1.joinable()) t1.join();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}
