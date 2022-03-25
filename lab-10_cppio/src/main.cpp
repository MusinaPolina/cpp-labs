#include <iostream>
#include <cstring>
#include "employees.h"

int main(int , char**) {
    std::string cmd;

    EmployeesArray array;
    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "load") {
            std::string file_name;
            std::cin >> file_name;
            //TODO()
        } else if (cmd == "add") {
            char *name = new char[101];
            int32_t type, base_salary;
            std::cin >> type >> name >> base_salary;
            if (type == 1) {
                Developer dev;
                std::cin >> dev;
                array.add(*dev);
            } else if (type == 2) {
                SalesManager sMan;
                std::cin >> sMan;
                array.add(*sMan);
            }
        } else if (cmd == "list") {
            std::cout << array;
        }
    }


    return 0;
}