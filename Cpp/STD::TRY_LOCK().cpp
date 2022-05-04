#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>

std::mutex m1,m2;

typedef unsigned long long ull;

int X=0,Y=0;

void waitForSeconds(int seconds){std::this_thread::sleep_for(std::chrono::seconds(seconds));}

void addIngredient(int& XorY,std::mutex& m,const char* desc){
    for(int i=0;i<5;++i){
        m.lock();
        ++XorY;
        std::cout << desc << " added"<< std::endl;
        m.unlock();
        waitForSeconds(1);
    }
}

void makeTea(){
    int count = 5,XplusY = 0;
    while(1){
        int lockresult = std::try_lock(m1,m2); //STD::TRY_LOCK()
        if(lockresult == -1){
            if(X!=0 && Y!=0){
                --count;
                XplusY = X+Y;
                X = Y = 0;
                std::cout << 5-count <<" - cup ready to serve!" << std::endl;
            }
            m1.unlock();
            m2.unlock();
            if(count == 0) break;
        }
    }
}


int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread thread1(addIngredient,std::ref(X),std::ref(m1),"milk");
    std::thread thread2(addIngredient,std::ref(Y),std::ref(m2),"sugar");
    std::thread thread3(makeTea);
    thread1.join();
    thread2.join();
    thread3.join();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Sec: " << duration.count()/1000000 << std::endl;
    std::cout << "Micro: " << duration.count()%1000000 << std::endl;
    return 0;
}
