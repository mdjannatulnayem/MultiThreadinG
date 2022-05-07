#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

std::timed_mutex mTX;

typedef unsigned long long ull;

ull buffer = 0;

void task(const char *threadNumber,int loopFor){
    std::unique_lock<std::timed_mutex> lock(mTX,std::defer_lock);
    if(lock.try_lock_for(std::chrono::seconds(1))){
    }
    for(int i=0;i<loopFor;i++){
        std::cout << threadNumber << " " << ++buffer << std::endl;
    }
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread t1(task,"T0",10);
    std::thread t2(task,"T1",21);
    if(t1.joinable()){
        t1.join();
    }
    if(t2.joinable()){
        t2.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}

