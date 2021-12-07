#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::map<int, int> fish_timers{
        { 8, 0 },
        { 7, 0 },
        { 6, 0 },
        { 5, 0 },
        { 4, 0 },
        { 3, 0 },
        { 2, 0 },
        { 1, 0 },
        { 0, 0 },
    };

    std::ifstream ifs{ "./in.txt" };
    for (int t; ifs >> t; ifs.get()) {
        ++fish_timers[t];
    }

    static constexpr int steps = 80;
    for (int i = 0; i < steps; ++i) {
        int last{};
        for (auto it = fish_timers.rbegin(); it != fish_timers.rend(); ++it) {
            if (it->first == 0) {
                fish_timers[8] += it->second;
                fish_timers[6] += it->second;
                fish_timers[it->first] = last;
            } else {
                int tmp = it->second;
                fish_timers[it->first] = last;
                last = tmp;
            }
        }
    }

    int sum{};
    for (auto [day, count] : fish_timers) {
        sum += count;
    }
    std::cout << sum << '\n';
}
