#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <vector>

class Employee {
public:
    Employee() = default;
    Employee(char *name, int32_t base_salary);
    ~Employee();

    virtual int salary() const = 0;

    virtual const Employee* operator*() const = 0;

    virtual void output(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream &os, const Employee &employee);
    friend std::istream& operator>>(std::istream &is, Employee &employee);

protected:
    char *_name;
    int32_t _base_salary;
};

class Developer: public Employee {
public:
    Developer() = default;
    Developer(char *name, int32_t base_salary, bool has_bonus);
    ~Developer() = default;

    int salary() const override;

    const Developer* operator*() const override;

    void output(std::ostream& os) const override;
    void input(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream &os, const Developer &developer);
    friend std::istream& operator>>(std::istream &os, Developer &developer);

private:
    bool _has_bonus;
};

class SalesManager: public Employee {
public:
    SalesManager() = default;
    SalesManager(char *name, int32_t base_salary, int32_t sold_nm, int32_t price);
    ~SalesManager()  = default;

    int salary() const override;

    const SalesManager* operator*() const override;

    void output(std::ostream& os) const override;
    void input(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream &os, const SalesManager &salesManager);
    friend std::istream& operator>>(std::istream &os, SalesManager &salesManager);

private:
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray() = default;

    void add(const Employee *e);
    int total_salary() const;

    friend std::ostream& operator<<(std::ostream &os, const EmployeesArray &array);

private:
    std::vector <Employee*> _employees;
};

#endif
