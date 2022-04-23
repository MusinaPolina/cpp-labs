#pragma once

#include <cstdint>
#include <iostream>
#include <queue>

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

    class CharOut {
    private:
        explicit CharOut(unsigned char s);

        unsigned char s;

    public:
        friend std::ostream &operator<<(std::ostream &os, CharOut manip);

        friend CharOut write_char(unsigned char s);
    };

    class CharIn {
    private:
        explicit CharIn(unsigned char &s);

        unsigned char &s;

    public:
        friend std::istream &operator>>(std::istream &is, CharIn manip);

        friend CharIn read_char(unsigned char &s);
    };

    std::ostream &operator<<(std::ostream &os, CharOut manip);
    std::istream &operator>>(std::istream &is, CharIn manip);
    CharOut write_char(unsigned char s);
    CharIn read_char(unsigned char &s);

    class ByteStreamOut {
    public:
        explicit ByteStreamOut(std::ostream &out);
        void put(bool elem);
        void close();

    private:
        void print_queue();

        std::ostream &out;
        std::queue<bool> q;
    };

    class ByteStreamIn {
    public:
        explicit ByteStreamIn(std::istream &in);
        void get(std::vector<bool> &code);
        bool get();

    private:
        void read_char();
        std::istream &in;
        std::queue<bool> q;
    };

}