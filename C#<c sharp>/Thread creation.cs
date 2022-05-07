using System;
using System.Threading;

namespace Threading //can be anyThing!!!
{
    class Program
    {
        static void Main(string[] args) //main function aka entryPoint!
        {
            Thread mainThread = Thread.CurrentThread;
            mainThread.Name = "Main";
            Thread thread2 = new Thread(() => countDown(21));
            Thread thread1 = new Thread(() => countUp(10));
            thread1.Start();
            thread2.Start();
            Console.WriteLine($"{mainThread.Name} thread going to sleep for 5 seconds!");
            Thread.Sleep(5000);
            if(thread1.IsAlive){
                thread1.Join();
                Console.WriteLine("Thread 1 succesfully joined!");
            }
            if(thread2.IsAlive){
                thread2.Join();
                Console.WriteLine("Thread 2 succesfully joined!");
            }
            System.Console.WriteLine($"Thread 1 running: {thread1.IsAlive}");
            System.Console.WriteLine($"Thread 2 running: {thread2.IsAlive}");
            Console.WriteLine($">>{mainThread.Name} thread exited the program!");
        }

        static void countUp(int loopFor){
            for(int i=1;i<=loopFor;i++){
                Console.WriteLine($"counting up until {loopFor} : {i}");
                Thread.Sleep(500);
            }
        }

        static void countDown(int loopFor){
            for(int i=loopFor;i>=1;i--){
                Console.WriteLine($"counting down until 1 : {i}");
                Thread.Sleep(500);
            }
        }
    }
}
