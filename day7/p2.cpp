#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

namespace util {
    template <typename It, typename Pred>
    It find(It begin, It end, Pred pred) {
        It it = begin;
        for (It i = begin + 1; i != end; ++i) {
            if (pred(it, i)) it = i;
        }
        return it;
    }

    template <typename It>
    It min(It begin, It end) {
        return util::find(begin, end, [](It min, It i){ return *min > *i; });
    }

    template <typename It>
    It max(It begin, It end) {
        return util::find(begin, end, [](It max, It i){ return *max < *i; });
    }
}

int main() {
    std::vector<int> vec;

    std::ifstream ifs{ "./c.txt" };
    for (int i; ifs.good(); ifs.get()) {
        ifs >> i;
        vec.push_back(i);
    }

    int min = *util::min(vec.cbegin(), vec.cend()), max = *util::max(vec.cbegin(), vec.cend());
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
    
    std::cout << *util::min(sums.cbegin(), sums.cend()) << '\n';
}
