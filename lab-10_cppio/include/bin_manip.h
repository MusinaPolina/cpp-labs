#pragma once

#include <stdint.h>
#include <iostream>


class BinManipulatorIntOut {
private:
    BinManipulatorIntOut(const int32_t &x);
    const int32_t &x;

public:
    friend std::ostream &operator<<(std::ostream &os, BinManipulatorIntOut manip);
    
    friend BinManipulatorIntOut write_le_int32(const int32_t &x);
};

class BinManipulatorIntIn {
private:
    BinManipulatorIntIn(int32_t &x);
    int32_t &x;

public:
    friend std::istream &operator>>(std::istream &is, BinManipulatorIntIn manip);

    friend BinManipulatorIntIn read_le_int32(int32_t &x);
};

BinManipulatorIntOut write_le_int32(const int32_t &x);
BinManipulatorIntIn read_le_int32(int32_t &x);

class BinManipulatorBoolOut {
private:
    BinManipulatorBoolOut(const bool &x);
    const bool &x;

public:
    friend std::ostream &operator<<(std::ostream &os, BinManipulatorBoolOut manip);

    friend BinManipulatorBoolOut write_bool(const bool &x);
};

class BinManipulatorBoolIn {
private:
    BinManipulatorBoolIn(bool &x);
    bool &x;

public:
    friend std::istream &operator>>(std::istream &is, BinManipulatorBoolIn manip);

    friend BinManipulatorBoolIn read_bool(bool &x);
};


BinManipulatorBoolOut write_bool(const bool &x);
BinManipulatorBoolIn read_bool(bool &x);

class BinManipulatorCharOut {
private:
    BinManipulatorCharOut(const char *s, size_t);
    const char *s;
    size_t sz;

public:
    friend std::ostream &operator<<(std::ostream &os, BinManipulatorCharOut manip);

    friend BinManipulatorCharOut write_c_str(const char *s);
};

class BinManipulatorCharIn {
private:
    BinManipulatorCharIn(char *s, size_t);
    char *s;
    size_t sz;

public:
    friend std::istream &operator>>(std::istream &is, BinManipulatorCharIn manip);

    friend BinManipulatorCharIn read_c_str(char *s, size_t sz);
};

BinManipulatorCharOut write_c_str(const char *s);
BinManipulatorCharIn read_c_str(char *s, size_t sz);

