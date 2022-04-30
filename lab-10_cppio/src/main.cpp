#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "employees.h"

int main(int , char**) {
    std::string cmd;
    std::cout << std::setprecision(5);
    EmployeesArray array;
    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "load") {
            std::string file_name;
            std::cin >> file_name;
            std::ifstream is(file_name, std::ios::binary);
            is >> array;
            is.close();
        } else if (cmd == "save") {
            std::string file_name;
            std::cin >> file_name;
            std::ofstream os(file_name, std::ios::binary);
            os << array;
            os.close();
        } else if (cmd == "add") {
            int type;
            std::cin >> type;
            Employee *employee = Employee::create(Employee::EmployeeType(type));
            assert(employee);
            std::cin >> *employee;
            array.add(employee);
        } else if (cmd == "list") {
            std::cout << array << '\n';
        }
    }
    return 0;
}