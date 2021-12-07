#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <array>

template <typename T>
typename std::vector<T>::iterator insert_sorted(std::vector<T> &vec, const T& val) {
    return vec.insert(std::upper_bound(vec.begin(), vec.end(), val), val);
}

struct table {
    void mark(short n) {
        for (int i = 0; i < 25; ++i) {
            int A{ i/5 }, Ao{ i%5 };
            if (m_set[A][Ao] == n) insert_sorted(m_marked_positions, i);
        }
    }
    const std::array<std::array<short, 5>, 5> &set() const {
        return m_set;
    }
    void insert(short n) {
        int A{ m_pos/5 }, Ao{ m_pos%5 };
        ++m_pos;
        m_set[A][Ao] = n;
    }
    void clear() {
        m_set.fill(std::array<short, 5>{});
        m_pos = 0;
    }
    bool bingo() const {
        for (int i = 0; i < 5; ++i) {
            int marked{};
            for (int k = 0; k < 5; ++k) {
                if (std::binary_search(m_marked_positions.cbegin(), m_marked_positions.cend(), i*5+k)) {
                    ++marked;
                }
            }
            if (marked == 5) return true;
        }
        for (int i = 0; i < 5; ++i) {
            int marked{};
            for (int k = i; k <= i + 20; k += 5) {
                if (std::binary_search(m_marked_positions.cbegin(), m_marked_positions.cend(), k)) {
                    ++marked;
                }
            }
            if (marked == 5) return true;
        }
        return false;
    }
    const std::vector<int> &marked() const {
        return m_marked_positions;
    }

    short &operator[](int idx) {
        int A{ idx/5 }, Ao{ idx%5 };
        return m_set[A][Ao];
    }
private:
    std::vector<int> m_marked_positions{};
    std::array<std::array<short, 5>, 5> m_set{};
    int m_pos{};
};
std::istream &operator>>(std::istream &is, table &t) {
    t.clear();
    for (int i = 0; i < 25; ++i) {
        int n;
        if (! (is >> n)) return is;
        t.insert(n);
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, const table &t) {
    std::for_each(t.set().cbegin(), t.set().cend(), [](const auto v) {
        std::for_each(v.cbegin(), v.cend(), [](const auto v1) { std::cout << v1 << ","; });
        std::endl(std::cout);
    });
    return os;
}

namespace util {
    bool is_bingo(const table &t) {
        return t.bingo();
    }
}

int main() {
    std::vector<table> tables;
    std::vector<int> numbers;
    std::ifstream ifs{ "./in.txt" };
    std::string set;
    std::getline(ifs, set);
    std::stringstream ss{ set };
    while (ss.good()) {
        int number; char d;
        ss >> number;
        ss >> d;
        numbers.push_back(number);
    }        
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    table _table;
    while (ifs >> _table) {
        tables.push_back(_table);
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        table lastcpy;
        auto remove = std::remove_if(tables.begin(), tables.end(), [&](table &t) {
            t.mark(numbers[i]);
            if (t.bingo()) {
                lastcpy = t;
                return true;
            } else {
                return false;
            }
        });
        tables.erase(remove, tables.end());
        if (tables.empty()) {
            std::cout << "Game over.\n";
            int marked_ptr{}, sum{};
            for (int i = 0; i < 25; ++i) {
                if (lastcpy.marked()[marked_ptr] == i) {
                    ++marked_ptr;
                } else {
                    sum += lastcpy[i];
                }
            }
            std::cout << sum * numbers[i];
            return 0;
        }
        // for (size_t k = 0; k < tables.size(); ++k) {
        //     tables[k].mark(numbers[i]);
        //     if (tables[k].bingo()) {
        //         // std::count_if(tables.begin(), tables.end(), util::is_bingo)
        //         if (1 == tables.size()) {
        //             std::cout << k << " is the last table to win.\n";
        //             table &t = tables[k];
        //             int marked_ptr{}, sum{};
        //             for (int i = 0; i < 25; ++i) {
        //                 if (t.marked()[marked_ptr] == i) {
        //                     ++marked_ptr;
        //                 } else {
        //                     sum += t[i];
        //                 }
        //             }
        //             std::cout << sum * numbers[i];
        //             return 0;
        //         }
        //     }
        // }
    }
}
