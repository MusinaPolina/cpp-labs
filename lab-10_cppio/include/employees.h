#pragma once

#include <stdint.h>
#include <iostream>
#include <vector>
#include "bin_manip.h"

class Employee {
public:
    Employee();
    Employee(const char *name, int32_t base_salary);
    Employee(const Employee &emp) = delete;
    virtual ~Employee();

    virtual Employee* clone() const = 0;

    [[nodiscard]] virtual int salary() const = 0;

    virtual const Employee* operator*() const = 0;

    friend std::ostream& operator<<(std::ostream &os, const Employee &employee);
    friend std::istream& operator>>(std::istream &is, Employee &employee);

    friend std::ofstream& operator<<(std::ofstream &os, const Employee &employee);
    friend std::ifstream& operator>>(std::ifstream &is, Employee &employee);

protected:
    virtual void output(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;

    virtual void outputf(std::ofstream& os) const = 0;
    virtual void inputf(std::ifstream& is) = 0;

    char *_name;
    static const size_t NAME_SIZE = 101;
    int32_t _base_salary;
};

class Developer: public Employee {
public:
    Developer() = default;
    Developer(const char *name, int32_t base_salary, bool has_bonus);
    Developer(const Developer &dev);
    ~Developer() =default;

    Developer* clone() const override;

    [[nodiscard]] int salary() const override;

    const Developer* operator*() const override;

    friend std::ostream& operator<<(std::ostream &os, const Developer &developer);
    friend std::istream& operator>>(std::istream &os, Developer &developer);

    friend std::ofstream& operator<<(std::ofstream &os, const Developer &developer);
    friend std::ifstream& operator>>(std::ifstream &os, Developer &developer);

protected:
    void output(std::ostream& os) const override;
    void input(std::istream& is) override;

    void outputf(std::ofstream& os) const override;
    void inputf(std::ifstream& is) override;

    bool _has_bonus;
};

class SalesManager: public Employee {
public:
    SalesManager() = default;
    SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price);
    SalesManager(const SalesManager &sMan);
    ~SalesManager()  = default;

    SalesManager* clone() const override;

    [[nodiscard]] int salary() const override;

    const SalesManager* operator*() const override;

    friend std::ostream& operator<<(std::ostream &os, const SalesManager &salesManager);
    friend std::istream& operator>>(std::istream &os, SalesManager &salesManager);

    friend std::ofstream& operator<<(std::ofstream &os, const SalesManager &salesManager);
    friend std::ifstream& operator>>(std::ifstream &os, SalesManager &salesManager);

protected:
    void output(std::ostream& os) const override;
    void input(std::istream& is) override;

    void outputf(std::ofstream& os) const override;
    void inputf(std::ifstream& is) override;

    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();

    void add(const Employee *e);
    [[nodiscard]] int total_salary() const;

    friend std::ostream& operator<<(std::ostream &os, const EmployeesArray &array);

    friend std::ofstream& operator<<(std::ofstream &os, const EmployeesArray &array);
    friend std::ifstream& operator>>(std::ifstream &is, EmployeesArray &array);

private:
    std::vector <Employee*> _employees;
};
