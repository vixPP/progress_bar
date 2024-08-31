#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <windows.h> 
#include "Timer.h"
#include <random>

using namespace std;

mutex mtx;
vector<pair<int, thread::id>> thread_info;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printTable()
{
    cout << "# \t   ID  \t     PROGRESS BAR \tTIME" << endl;
}


void draw(int num)
{
    Timer timer;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100, 1000);

    mtx.lock();
    cout << num << "\t   " << this_thread::get_id() << "     " << endl;
    Sleep(4);
    mtx.unlock();

    int Calc_length = 12;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < Calc_length; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(dis(gen)));
        mtx.lock();
        gotoxy(21 + i, num + 1);
        cout << (char)219;
        mtx.unlock();
        
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    mtx.lock();
    cout << "\t" << duration << "s";
    mtx.unlock();
}

void task()
{
    const int numThreads = 5;
    vector<thread> threads;

    for (int i = 0; i < numThreads; i++)
    {
        threads.emplace_back(draw, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

}



int main()
{
    setlocale(LC_ALL, ".866");

    printTable();

    task();

    gotoxy(2, 7);
    cout << "PROGRESSBAR finished the job" << endl;

    return 0;
}