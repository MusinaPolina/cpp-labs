#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "bin_manip.h"

class Employee {
public:
    Employee() = default;
    Employee(std::string name, int32_t base_salary);
    Employee(const Employee &emp) = delete;
    virtual ~Employee() = default;

    [[nodiscard]] virtual int salary() const = 0;

    virtual const Employee* operator*() const = 0;

    friend std::ostream& operator<<(std::ostream &os, const Employee &employee);
    friend std::istream& operator>>(std::istream &is, Employee &employee);

    friend std::ofstream& operator<<(std::ofstream &os, const Employee &employee);
    friend std::ifstream& operator>>(std::ifstream &is, Employee &employee);

protected:
    void base_outputf(std::ostream& os) const;
    void base_inputf(std::istream& is);

    virtual void output(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;

    virtual void outputf(std::ofstream& os) const = 0;
    virtual void inputf(std::ifstream& is) = 0;

    std::string _name;
    int32_t _base_salary;
    static const size_t NAME_SIZE = 101;
};

class Developer: public Employee {
public:
    Developer() = default;
    Developer(std::string name, int32_t base_salary, bool has_bonus);
    Developer(const Developer &dev);
    ~Developer() override =default;

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
    SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price);
    SalesManager(const SalesManager &sMan);
    ~SalesManager() override = default;

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
    std::vector<const Employee*> _employees;
};
