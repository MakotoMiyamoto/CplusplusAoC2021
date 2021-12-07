#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

struct coordinate {
    coordinate(int x, int y) : m_x{ x }, m_y{ y } {}
    int m_x{}, m_y{};
};

int smallest(int x, int y) {
    if (x < y) return x;
    return y;
}

int biggest(int x, int y) {
    if (x > y) return x;
    return y;
}

int main() {
    // one-dimensional
    // formula: (x, y) = y * N / mag + x
    std::vector<coordinate> coordinates;

    FILE *fp = fopen("./in.txt", "r");
    int x1, x2, y1, y2, largest;
    while (fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        if (y1 == y2) for (int xit = smallest(x1, x2); xit <= biggest(x1, x2); ++xit) {
            coordinates.push_back(coordinate{ xit, y1 });
        }
        else if (x1 == x2) for (int yit = smallest(y1, y2); yit <= biggest(y1, y2); ++yit) {
            coordinates.push_back(coordinate{ x1, yit });
        }
        if (x1 > largest) largest = x1; if (x2 > largest) largest = x2;
        if (y1 > largest) largest = y1; if (y2 > largest) largest = y2;
    }
    int mag = pow(10, (int)log10(largest) + 1);

    int N = pow(mag, 2); // square size of the coordinate plane
    std::vector<int> flatcoords(N, 0);
    std::cout << flatcoords.size() << '\n';
    std::cout << coordinates.size() << '\n';

    std::for_each(coordinates.begin(), coordinates.end(), [&](const coordinate &coord) {
        int pos = coord.m_y * N / mag + coord.m_x;
        //std::cout << pos << '\n';
        //std::cout << "(" << coord.m_x << ", " << coord.m_y << ") = " << pos << '\n';
        ++flatcoords[pos];
    });
    int overlap = std::count_if(flatcoords.begin(), flatcoords.end(), [](const auto &c) { return c > 1; });
    std::cout << overlap << '\n';
}
