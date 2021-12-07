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

struct range {
    range(int x1, int y1, int x2, int y2) : m_c1{ x1, y1 }, m_c2{ x2, y2 } {}
    const coordinate &c1() const {
        return m_c1;
    }
    const coordinate &c2() const {
        return m_c2;
    }
private:
    coordinate m_c1, m_c2;
};

int smallest(int x, int y) {
    if (x < y) return x;
    return y;
}

int biggest(int x, int y) {
    if (x > y) return x;
    return y;
}

coordinate smallest_c(coordinate c1, coordinate c2) {
    if (c1.m_y == c2.m_y) {
        if (c1.m_x > c2.m_x) return c1;
        return c2;
    }
    else if (c1.m_y > c2.m_y) {
        return c2;
    }
    return c1;
}

coordinate biggest_c(coordinate c1, coordinate c2) {
    if (c1.m_y == c2.m_y) {
        if (c1.m_x > c2.m_x) return c2;
        return c1;
    }
    else if (c1.m_y > c2.m_y) {
        return c1;
    }
    return c2;
}

int main() {
    // one-dimensional; from 0-9, (x, y) = x * 10 + y
    // formula: (x, y) = y * N / mag + x
    std::vector<coordinate> coordinates;
    std::vector<range> ranges;

    FILE *fp = fopen("./in.txt", "r");
    int x1, x2, y1, y2, largest;
    while (fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        if (y1 == y2) for (int xit = smallest(x1, x2); xit <= biggest(x1, x2); ++xit) {
            coordinates.push_back(coordinate{ xit, y1 });
        }
        else if (x1 == x2) for (int yit = smallest(y1, y2); yit <= biggest(y1, y2); ++yit) {
            coordinates.push_back(coordinate{ x1, yit });
        }
        else {
            //ranges.push_back(range{ x1, y1, x2, y2 });

            coordinate c1{ x1, y1 }, c2{ x2, y2 };
            coordinate cs = smallest_c(c1, c2), cb = biggest_c(c1, c2);
            if (cs.m_x < cb.m_x) {
                // descending line
                int x = cs.m_x;
                for (int y = cs.m_y; y <= cb.m_y; ++y) {
                    coordinates.push_back(coordinate{ x, y });
                    ++x;
                }
            }
            else {
                // ascending line
                int x = cs.m_x;
                for (int y = cs.m_y; y <= cb.m_y; ++y) {
                    coordinates.push_back(coordinate{ x, y });
                    --x;
                }
            }
        }
        if (x1 > largest) largest = x1; if (x2 > largest) largest = x2;
        if (y1 > largest) largest = y1; if (y2 > largest) largest = y2;
    }

    int mag = pow(10, (int)log10(largest) + 1);
    int N = pow(mag, 2); // square size of the coordinate plane
    std::vector<int> flatcoords(N, 0);

    std::for_each(coordinates.begin(), coordinates.end(), [&](const coordinate &coord) {
        int pos = coord.m_y * N / mag + coord.m_x;
        ++flatcoords[pos];
    });
    int overlap = std::count_if(flatcoords.begin(), flatcoords.end(), [](const auto &c) { return c > 1; });
    std::cout << overlap << '\n';
}
