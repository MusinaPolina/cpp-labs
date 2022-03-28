#pragma once

#include <cstdint>
#include <iostream>

namespace BinManipulator {
    class IntOut {
    private:
        explicit IntOut(const int32_t &x);

        const int32_t &x;

    public:
        friend std::ostream &operator<<(std::ostream &os, IntOut manip);

        friend IntOut write_le_int32(const int32_t &x);
    };

    class IntIn {
    private:
        explicit IntIn(int32_t &x);

        int32_t &x;

    public:
        friend std::istream &operator>>(std::istream &is, IntIn manip);

        friend IntIn read_le_int32(int32_t &x);
    };

    std::ostream &operator<<(std::ostream &os, IntOut manip);
    std::istream &operator>>(std::istream &is, IntIn manip);
    IntOut write_le_int32(const int32_t &x);
    IntIn read_le_int32(int32_t &x);


    class BoolOut {
    private:
        explicit BoolOut(bool x);

        bool x;

    public:
        friend std::ostream &operator<<(std::ostream &os, BoolOut manip);

        friend BoolOut write_bool(bool x);
    };

    class BoolIn {
    private:
        explicit BoolIn(bool &x);

        bool &x;

    public:
        friend std::istream &operator>>(std::istream &is, BoolIn manip);

        friend BoolIn read_bool(bool &x);
    };

    std::ostream &operator<<(std::ostream &os, BoolOut manip);
    std::istream &operator>>(std::istream &is, BoolIn manip);
    BoolOut write_bool(bool x);
    BoolIn read_bool(bool &x);


    class CharOut {
    private:
        explicit CharOut(const char *s, size_t);

        const char *s;
        size_t sz;

    public:
        friend std::ostream &operator<<(std::ostream &os, CharOut manip);

        friend CharOut write_c_str(const char *s);
    };

    class CharIn {
    private:
        explicit CharIn(char *s, size_t);

        char *s;
        size_t sz;

    public:
        friend std::istream &operator>>(std::istream &is, CharIn manip);

        friend CharIn read_c_str(char *s, size_t sz);
    };

    std::ostream &operator<<(std::ostream &os, CharOut manip);
    std::istream &operator>>(std::istream &is, CharIn manip);
    CharOut write_c_str(const char *s);
    CharIn read_c_str(char *s, size_t sz);
}