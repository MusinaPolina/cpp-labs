#include <cassert>
#include "matrix.h"
#include "iostream"

int main(int argc, char* argv[]) {
    std::vector <Matrix> regs(10);
    while (std::cin) {
        std::string cmd;
        size_t reg;
        std::cin >> cmd;
        if (cmd == "load") {
            std::string fname;
            std::cin >> reg >> fname;
            regs[reg] = Matrix::load(fname);
        } else if (cmd == "print") {
            std::cin >> reg;
            std::cout << regs[reg];
        } else if (cmd == "add") {
            size_t oth;
            std::cin >> reg >> oth;
            regs[reg] += regs[oth];
        } else if (cmd == "mul") {
            size_t oth;
            std::cin >> reg >> oth;
            regs[reg] += regs[oth];
        } else if (cmd == "elem") {
            size_t row, col;
            std::cin >> reg >> row >> col;
            std::cout << regs[reg][row][col];
        } else {
            assert(cmd == "exit");
            break;
        }
    }
    return 0;
}