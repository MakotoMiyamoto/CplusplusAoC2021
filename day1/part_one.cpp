#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream ifs{ "./in.txt" };
    int n, p, c = 0;
    ifs >> n;
    p = n;
    while (ifs >> n) {
        if (n > p) {
            ++c;
        }
        p = n;
    }
    std::cout << c << '\n';
}
