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
    for (int i = min; i < max; ++i) {
        sums.push_back(sum_diff(vec.cbegin(), vec.cend(), i));
    }
    
    std::cout << *util::min(sums.cbegin(), sums.cend()) << '\n';
}
