#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <limits>
#include <iterator>

constexpr size_t bits = 5ULL;

int main() {
    short weight_array[bits] = {};
    unsigned short gamma{}, epsilon;
    std::ifstream ifs{ "./test.txt" };
    while (ifs.good()) {
        for (size_t i = 0; i < bits; ++i) {
            int bit = ifs.get() - '0';
            weight_array[i] += bit * 1 + !bit * -1;
        }
        if (ifs.peek() == '\n') ifs.get();
    }
    std::copy(weight_array, weight_array + bits, std::ostream_iterator<short>{ std::cout, ", " });

    std::bitset<bits> b_gamma{0};
    for (size_t i = 0; i < bits; ++i) {
        b_gamma[i] = weight_array[i] > 0 ? 1 : 0;
    }
    std::cout << b_gamma << '\n';
}
