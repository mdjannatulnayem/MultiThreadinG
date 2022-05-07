#include <chrono>
#include <thread>
#include <iostream>
#include <future>

typedef unsigned long long ull;

ull findOdd(ull start,ull end){
    ull oddSum = 0;
    for(ull i=start;i<=end;i++){
        if(i & 1){
            oddSum += i;
        }
    }
    return oddSum;
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    ull start = 0, end = 1900000000;
    //Creating a Task
    std::future<ull> oddFuture
        = std::async(std::launch::async,findOdd,start,end);
    //Task returns result
    std::cout << "Waiting for result!!!" << std::endl;
    //assume thousand lines of code 😴 in between...!
    std::cout << "Odd sum: " << oddFuture.get() << std::endl;
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}
