#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main() {
    std::vector<int> vec;

    std::ifstream ifs{ "./c.txt" };
    for (int i; ifs.good(); ifs.get()) {
        ifs >> i;
        vec.push_back(i);
    }

    int min = *std::min_element(vec.cbegin(), vec.cend()),
        max = *std::max_element(vec.cbegin(), vec.cend());
    std::vector<int> sums;
    int step{};
    for (int i = min; i < max; ++i) {
        int sum{};
        for (const auto &x : vec) {
            int diff = std::abs(x - i);
            sum += diff * (diff + 1) / 2;
        }
        std::cout << i << ": " << sum << '\n';
        sums.push_back(sum);
    }
    
    std::cout << *std::min_element(sums.cbegin(), sums.cend()) << '\n';
}
