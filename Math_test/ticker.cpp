#include <stdio.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std::chrono;

int timetable[5] ={0,0,0,0,0};

int func_dur;
void Ticker_task(){

    for(int i; i < 5; i++){
        func_dur = timetable[i];
        std::cout << func_dur << "\n";

        
    }
    
}
int main(){

    auto start = high_resolution_clock::now();
    std::cout << start;
    std::cout << "1st?";
    std::cin >> timetable[0];
    std::cout << start;

    std::cout << "2nd?";
    std::cin >> timetable[1];
    std::cout << start;
    std::cout << "3rd?";
    std::cin >> timetable[2];
    std::cout << start;
    std::cout << "4th?";
    std::cin >> timetable[3];
    std::cout << start;
    std::cout << "5th?";
    std::cin >> timetable[4];
    Ticker_task();
return 1;
}