#include <cstring>
#include <cassert>
#include <fstream>
#include "employees.h"

Employee::Employee(std::string name, int32_t base_salary): _name(name), _base_salary(base_salary) {};

std::ostream& operator<<(std::ostream &os, const Employee &emp) {
    emp.output(os);
    return os ;
}

std::istream& operator>>(std::istream &is, Employee &emp) {
    emp.input(is);
    return is;
}

std::ofstream& operator<<(std::ofstream &os, const Employee &emp) {
    emp.outputf(os);
    return os ;
}

std::ifstream& operator>>(std::ifstream &is, Employee &emp) {
    emp.inputf(is);
    return is;
}

void Employee::base_outputf(std::ostream& os) const {
    os << write_c_str(_name.c_str()) << write_le_int32(_base_salary);
}

void Employee::base_inputf(std::istream& is) {
    char *name = new char[NAME_SIZE];
    is >> read_c_str(name, NAME_SIZE) >> read_le_int32(_base_salary);
    _name = name;
    delete[] name;
}

Developer::Developer(std::string name, int32_t base_salary, bool has_bonus):
    Employee(name, base_salary), _has_bonus(has_bonus) {};

Developer::Developer(const Developer &dev):
    Developer(dev._name, dev._base_salary, dev._has_bonus) {};

Developer* Developer::clone() const {
    return new Developer(*this);
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

const Developer* Developer::operator*() const { return this; }

void Developer::output(std::ostream &os) const {
    os << *this;
}

void Developer::input(std::istream &is) {
    is >> *this;
}

void Developer::outputf(std::ofstream &os) const {
    os << *this;
}

void Developer::inputf(std::ifstream &is) {
    is >> *this;
}

std::ostream& operator<<(std::ostream &os, const Developer &dev) {
    os << "Developer\nName: " << dev._name << "\nBase Salary: " << dev._base_salary << "\n";
    os << "Has bonus: " << (dev._has_bonus ? "+" : "-");
    return os;
}

std::istream& operator>>(std::istream &is, Developer &dev) {
    is >> dev._name >> dev._base_salary >> dev._has_bonus;
    return is;
}

std::ofstream& operator<<(std::ofstream &os, const Developer &dev) {
    os << write_le_int32(1);
    dev.base_outputf(os);
    os << write_bool(dev._has_bonus);
    return os;
}

std::ifstream& operator>>(std::ifstream &is, Developer &dev) {
    dev.base_inputf(is);
    is >> read_bool(dev._has_bonus);
    return is;
}

SalesManager::SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price):
    Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {};

SalesManager::SalesManager(const SalesManager & sMan):
    SalesManager(sMan._name, sMan._base_salary, sMan._sold_nm, sMan._price) {};

SalesManager* SalesManager::clone() const {
    return new SalesManager(*this);
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

const SalesManager* SalesManager::operator*() const { return this; }

void SalesManager::output(std::ostream& os) const {
    os << *this;
}

void SalesManager::input(std::istream &is) {
    is >> *this;
}

void SalesManager::outputf(std::ofstream& os) const {
    os << *this;
}

void SalesManager::inputf(std::ifstream &is) {
    is >> *this;
}

std::ostream& operator<<(std::ostream &os, const SalesManager &sMan) {
    os << "Sales Manager\nName: " << sMan._name << "\nBase Salary: " << sMan._base_salary << "\n";
    os << "Sold items: " << sMan._sold_nm << "\nItem price: " << sMan._price;
    return os ;
}

std::istream& operator>>(std::istream &is, SalesManager &sMan) {
    return is >> sMan._name >> sMan._base_salary >> sMan._sold_nm >> sMan._price;
}

std::ofstream& operator<<(std::ofstream &os, const SalesManager &sMan) {
    os << write_le_int32(2);
    sMan.base_outputf(os);
    os << write_le_int32(sMan._sold_nm) << write_le_int32(sMan._price);
    return os ;
}

std::ifstream& operator>>(std::ifstream &is, SalesManager &sMan) {
    sMan.base_inputf(is);
    is >> read_le_int32(sMan._sold_nm) >> read_le_int32(sMan._price);
    return is;
}

EmployeesArray::~EmployeesArray() {
    for (auto employee: _employees) {
        delete employee;
    }
}

std::ostream& operator<<(std::ostream &os, const EmployeesArray &array) {
    for (size_t i = 0; i < array._employees.size(); i++) {
        os << i + 1 << ". ";
        os << *array._employees[i];
        os << '\n';
    }
    os << "== Total salary: " << array.total_salary() << '\n';
    return os ;
}

std::ofstream& operator<<(std::ofstream &os, const EmployeesArray &array) {
    os << write_le_int32(array._employees.size());
    for (auto employee: array._employees) {
        os << *employee;
    }
    return os;
}

std::ifstream& operator>>(std::ifstream &is, EmployeesArray &array) {
    int32_t sz;
    is >> read_le_int32(sz);
    for (int32_t i = 0; i < sz; i++) {
        int32_t type;
        is >> read_le_int32(type);
        if (type == 1) {
            Developer *dev = new Developer;
            is >> *dev;
            array.add(dev);
        } else if (type == 2) {
            SalesManager *sMan = new SalesManager;
            is >> *sMan;
            array.add(sMan);
        }
    }
    return is;
}

void EmployeesArray::add(const Employee *emp) {
    assert(emp != nullptr);
    _employees.push_back(emp);
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (auto employee : _employees) {
        total += employee->salary();
    }
    return total;
}