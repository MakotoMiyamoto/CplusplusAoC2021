#include <iostream>
#include <fstream>
#include <string>

int main() {
    int p{ 0 }, d{ 0 }, a{ 0 };
    std::ifstream ifs{ "./in.txt" };
    std::string cmd, arg;
    while (ifs.good()) {
        ifs >> cmd >> arg;
        int iarg = std::stoi(arg);
        if (cmd == "forward") {
            p += iarg;
            d += a * iarg;
        } else if (cmd == "up") {
            a -= iarg;
        } else if (cmd == "down") {
            a += iarg;
        }
    }
    std::cout << "Pos: " << p << ", Dep: " << d << ", Aim: " << a << '\n';
    std::cout << "Prd: " << p * d << '\n';
}
