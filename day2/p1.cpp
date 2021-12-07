#include <iostream>
#include <fstream>
#include <string>

int main() {
    int p = 0, d = 0;
    std::ifstream ifs{ "./in.txt" };
    std::string cmd, arg;
    while (ifs.good()) {
        ifs >> cmd >> arg;
        int iarg = std::stoi(arg);
        if (cmd == "forward") {
            p += iarg;
        } else if (cmd == "up") {
            d -= iarg;
        } else if (cmd == "down") {
            d += iarg;
        }
    }

    std::cout << "Pos: " << p << ", Depth: " << d << '\n';
    std::cout << "Prd: " << p * d << '\n';
}   
