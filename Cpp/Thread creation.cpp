#include <chrono>
#include <thread>
#include <iostream>

typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findOdd(ull start,ull end){
    for(ull i = start; i <= end; ++i){
        if((i & 1)!=0){
            oddSum  += i;
        }
    }
}

void findEven(ull start,ull end){
    for(ull i = start; i <= end; ++i){
        if((i & 1)==0){
            evenSum  += i;
        }
    }
}

int main()
{
    ull start = 0, end = 1900000000;
    auto startTime = std::chrono::high_resolution_clock::now();
    //findOdd(start,end);
    //findEven(start,end);
    std::thread thread1(findOdd,start,end);
    std::thread thread2(findEven,start,end);
    /*
    *million line code 😴
    */
    if(thread1.joinable()){
        thread1.join();
    }
    if(thread2.joinable()){
        thread2.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Odd sum: " << oddSum << std::endl;
    std::cout << "Even sum: " << evenSum << std::endl;
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}
