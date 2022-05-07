#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

std::mutex mTX;
std::condition_variable cV;

typedef unsigned long long ull;

ull balance = 0;

void addMoney(int money){
    std::lock_guard<std::mutex> lock(mTX);
    balance += money;
    std::cout << "Amount added.Current balance: " << balance << std::endl;
    cV.notify_one();
}

void withdrawMoney(int money){
    std::unique_lock<std::mutex> ulock(mTX);
    cV.wait(ulock,[]{return (balance != 0)?true:false;}); //cV WAITS IF FALSE
    if(balance >= money){
        balance -= money;
        std::cout << "Amount deducted: " << money << std::endl;
    }else{
        std::cout << "Not enough money!" << std::endl;
    }
    std::cout << "Current balance is: " << balance << std::endl;
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread t1(withdrawMoney,1000);
    std::thread t2(addMoney,1200);
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
