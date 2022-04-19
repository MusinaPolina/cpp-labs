#include <cassert>
#include "matrix.h"
#include "iostream"

size_t reg_to_int(std::string reg) {
    return reg[1] - '0';
}

int main(int argc, char* argv[]) {
    try {
        std::vector <Matrix> regs(10);
        while (std::cin) {
            std::string cmd, reg;
            std::cin >> cmd;
            if (cmd == "load") {
                std::string fname;
                std::cin >> reg >> fname;
                try {
                    regs[reg_to_int(reg)] = Matrix::load(fname);
                } catch (const UnableOpenFileException& e){
                    std::cout << e.what() << std::endl;
                } catch (const InvalidFileFormatException& e){
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
                } catch (const AddException& e){
                    std::cout << e.what() << std::endl;
                }
            } else if (cmd == "mul") {
                std::string oth;
                std::cin >> reg >> oth;
                try {
                    regs[reg_to_int(reg)] += regs[reg_to_int(oth)];
                } catch (const MulException& e){
                    std::cout << e.what() << std::endl;
                }
            } else if (cmd == "elem") {
                size_t row, col;
                std::cin >> reg >> row >> col;
                try {
                    std::cout << regs[reg_to_int(reg)][row][col];
                } catch (const AccessException& e){
                    std::cout << e.what() << std::endl;
                }
            } else {
                assert(cmd == "exit");
                break;
            }
        }
    } catch (const std::bad_alloc& e) {
        std::cout << BadAllocException().what() << std::endl;
    }
    return 0;
}