#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

std::mutex mTX;

typedef unsigned long long ull;

ull myPoint = 0;

void addPoint(ull time){
    while(time--){
        //mTX.lock();
        if(mTX.try_lock()){
            myPoint += 1;
            mTX.unlock();
        }
    }
}

int main()
{
    ull x;
    std::cin >> x;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread thread1(addPoint,x);
    std::thread thread2(addPoint,x);
    if(thread1.joinable()){
        thread1.join();
    }
    if(thread2.joinable()){
        thread2.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "My point: " << myPoint << std::endl;
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}
