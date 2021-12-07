#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using fit_t = std::istream_iterator<std::string>;

template <typename Predicate>
void hate_hardcode(std::vector<std::string> &vec, Predicate pred) {
    for (size_t i = 0; i < vec.front().size() && vec.size() > 1; ++i) {
        std::vector<std::string> tmp;
        int o{};
        std::for_each(vec.begin(), vec.end(), [&](const auto s) {
            if (s[i] == '1') o += 1;
            else o -= 1;
        });
        auto res = std::remove_if(vec.begin(), vec.end(), [&](const auto s) {
            return pred(i, o, s);
        });
        vec.erase(res, vec.end());
    }
}

int main() {
    std::ifstream ifs{ "./in.txt" };
    std::vector<std::string> o2_vec{ fit_t{ ifs }, fit_t{} }, co2_vec = o2_vec;
    size_t start = 0, stop = 2;
    hate_hardcode(o2_vec, [](int idx, int o, const auto s) {
        if (o >= 0) return s[idx] != '1';
        else return s[idx] != '0';
    });
    hate_hardcode(co2_vec, [](int idx, int o, const auto s) {
        if (o >= 0) return s[idx] != '0';
        else return s[idx] != '1';
    });
    int o2{ std::stoi(o2_vec.front(), 0, 2) }, co2{ std::stoi(co2_vec.front(), 0, 2) };
    std::cout << o2 * co2 << '\n';
}
