#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include "Timer.h"


using namespace std;

mutex m;

void printTable()
{
    cout << "# \t   ID  \t     PROGRESS BAR \tTIME" << endl;
}

void ProgressBar()
{
    
    int Calc_length = 12;
    for (int i = 0; i < Calc_length; i++)
    {
        cout << '#';
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    
}

void threadInfo(int num)
{
    cout << num << "\t   " << this_thread::get_id() << "     ";
    ProgressBar();
    cout << "     ";

    SimpleTimer timer;

    this_thread::sleep_for(chrono::milliseconds(200));
}

void task()
{
    const int numThreads = 5;

    thread* t = new thread[numThreads];
    for (int i = 0; i < numThreads; i++) 
    {
        std::thread t(threadInfo, i);
        t.join(); 
        cout << endl;
    }
}

int main() 
{
    printTable();

    task();
    
    return 0;
}