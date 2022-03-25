#include <cstring>
#include <cassert>
#include "employees.h"

Employee::Employee(char *name, int32_t base_salary): _base_salary(base_salary) {
    size_t len = strlen(name) + 1;
    _name = new char[len + 1];
    strncpy(_name, name, len);
}

Employee::~Employee() {
    delete _name;
}

std::ostream& operator<<(std::ostream &os, const Employee &emp) {
    emp.output(os);
    return os ;
}

std::istream& operator>>(std::istream &is, Employee &emp) {
    emp.input(is);
    return is;
}

Developer::Developer(char *name, int32_t base_salary, bool has_bonus):
    Employee(name, base_salary), _has_bonus(has_bonus) {}

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

std::ostream& operator<<(std::ostream &os, const Developer &dev) {
    os << "Developer\nName: " << dev._name << "\nBase Salary: " << dev._base_salary << "\n";
    os << "Has bonus: " << (dev._has_bonus ? "+" : "-");
    return os;
}

std::istream& operator>>(std::istream &is, Developer &dev) {
    dev._name =
    return is >> dev._name >> dev._base_salary >> dev._has_bonus;
}

SalesManager::SalesManager(char *name, int32_t base_salary, int32_t sold_nm, int32_t price):
    Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

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

std::ostream& operator<<(std::ostream &os, const SalesManager &sMan) {
    os << "Sales Manager\nName: " << sMan._name << "\nBase Salary: " << sMan._base_salary << "\n";
    os << "Sold items: " << sMan._sold_nm << "\nItem price: " << sMan._price;
    return os ;
}

std::istream& operator>>(std::istream &is, SalesManager &sMan) {
    return is >> sMan._name >> sMan._base_salary >> sMan._price;
}


std::ostream& operator<<(std::ostream & os, const EmployeesArray &array) {
    for (auto employee: array._employees) {
        os << *employee << '\n';
    }
    os << "== Total salary: " << array.total_salary() << '\n';
    return os ;
}

void EmployeesArray::add(const Employee *e) {
    assert(e != nullptr);
    _employees.push_back(const_cast<Employee *>(e));
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (auto employee : _employees) {
        total += employee->salary();
    }
    return total;
}