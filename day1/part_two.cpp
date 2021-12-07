#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream ifs{ "./in.txt" };
    std::vector<int> set;
    for (int n; ifs >> n; set.push_back(n));
    int pch = set[0] + set[1] + set[2], c = 0;
    for (size_t i = 1; i < set.size() - 2; ++i) {
        int chunk = set[i] + set[i+1] + set[i+2];
        if (chunk > pch) ++c;
        pch = chunk;
    }
    std::cout << c << '\n';
}
