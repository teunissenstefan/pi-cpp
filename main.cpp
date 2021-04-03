#include <iostream>
#include <iomanip>
#include <chrono>
#include <map>
#include "math.h"

//
// Of all the patterns that I could create
//  I built a labyrinth with no escape
//  To keep myself under lock and key
//  I am my own worst enemy
//


double piLeibniz(int64_t max) {
    double pi = 1;
    int calcToggle = 1;
    for (int64_t i = 3; i < max; i++) {
        if (i % 2 == 0)continue;
        double cur = 1.0 / i;
        pi = calcToggle ? pi - cur : pi + cur;
        calcToggle = calcToggle ? 0 : 1;
    }
    return pi * 4.0;
}

double piNilakantha(int64_t max) {
    double pi = 3;
    int calcToggle = 0;
    for (int64_t i = 2; i < max; i += 2) {
        double cur = (4.0 / (i * (i + 1.0) * (i + 2.0)));
        pi = calcToggle ? pi - cur : pi + cur;
        calcToggle = calcToggle ? 0 : 1;
    }
    return pi;
}

double piViete(int64_t max) {//24
    double pi = 2;
    for (int64_t i = 0; i < max; i++) {
        double cur = sqrt(2);
        for (int64_t j = 0; j < i; j++) {
            cur = sqrt(2 + cur);
        }
        cur = 2 / cur;
        pi *= cur;
    }
    return pi;
}

typedef double (*FnPtr)(int64_t);

int main() {
    std::map<FnPtr, int64_t> m{
            {piLeibniz,    1'000'000'000},//1'000'000'000'000
            {piNilakantha, 1'000'000'000},
            {piViete,      24},
    };

    for (auto const &x : m) {
        auto start = std::chrono::steady_clock::now();
        std::time_t startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::ctime(&startTime);

        double pi = x.first(x.second);

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setprecision(20);
        std::cout << pi << std::endl;
        std::cout << "3.1415926535897932384" << std::endl;
        std::time_t endTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "Time taken: " << duration.count() / 1'000'000 << " seconds | " << std::ctime(&endTime)
                  << std::endl;
    }
    std::string str = "notify-send \"3.14\ndone\" ";
    system(str.c_str());
    return 0;
}
