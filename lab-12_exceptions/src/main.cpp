#include <cassert>
#include "matrix.h"
#include "iostream"

static size_t reg_to_int(std::string reg) {
    return reg[1] - '0';
}

int main(int argc, char* argv[]) {
    std::vector <Container::Matrix> regs(10);
    while (std::cin) {
        std::string cmd, reg;
        std::cin >> cmd;
        if (cmd == "load") {
            std::string fname;
            std::cin >> reg >> fname;
            try {
                regs[reg_to_int(reg)] = Container::Matrix::load(fname);
            } catch (const std::exception& e){
                std::cout << e.what() << std::endl;
            }
        } else if (cmd == "print") {
            std::cin >> reg;
            std::cout << regs[reg_to_int(reg)];
        } else if (cmd == "add") {
            std::string oth;
            std::cin >> reg >> oth;
            try {
                regs[reg_to_int(reg)] += regs[reg_to_int(oth)];
            } catch (const std::exception& e){
                std::cout << e.what() << std::endl;
            }
        } else if (cmd == "mul") {
            std::string oth;
            std::cin >> reg >> oth;
            try {
                regs[reg_to_int(reg)] *= regs[reg_to_int(oth)];
            } catch (const std::exception& e){
                std::cout << e.what() << std::endl;
            }
        } else if (cmd == "elem") {
            size_t row, col;
            std::cin >> reg >> row >> col;
            try {
                std::cout << regs[reg_to_int(reg)][row][col] << std::endl;
            } catch (const std::exception& e){
                std::cout << e.what() << std::endl;
            }
        } else {
            assert(cmd == "exit");
            break;
        }
    }
    return 0;
}