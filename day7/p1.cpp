#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

template <typename T, typename It>
T sum_diff(It begin, It end, const T &u) {
    T t{};
    std::for_each(begin, end, [&](const auto &ui){ t += std::abs(ui - u); });
    return t;
}

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
    for (int i = min; i < max; ++i) {
        sums.push_back(sum_diff(vec.cbegin(), vec.cend(), i));
    }
    
    std::cout << *std::min_element(sums.cbegin(), sums.cend()) << '\n';
}
