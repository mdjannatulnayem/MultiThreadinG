#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

std::recursive_mutex mTX;

typedef unsigned long long ull;

ull buffer = 0;

void recursion(char c,int loopFor){
    if(loopFor < 0){
        return;
    }
    if(mTX.try_lock()){
        std::cout << c << " " << buffer++ << std::endl;
        recursion(c,--loopFor);
        mTX.unlock();
    }
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread t1(recursion,'0',10);
    std::thread t2(recursion,'1',21);
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
