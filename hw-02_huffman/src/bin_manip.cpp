#include <cstring>
#include "bin_manip.h"
#include <climits>

namespace BinManipulator {

    IntOut::IntOut(const int32_t &x) : x(x) {}

    IntIn::IntIn(int32_t &x) : x(x) {}


    std::ostream &operator<<(std::ostream &os, IntOut manip) {
        return os.write(reinterpret_cast<const char *>(&manip.x), sizeof(manip.x));
    }

    std::istream &operator>>(std::istream &is, IntIn manip) {
        return is.read(reinterpret_cast<char *>(&manip.x), sizeof(manip.x));
    }

    IntOut write_le_int32(const int32_t &x) { return IntOut(x); }

    IntIn read_le_int32(int32_t &x) { return IntIn(x); }


    CharOut::CharOut(unsigned char s) : s(s) {}

    CharIn::CharIn(unsigned char &s) : s(s) {}

    std::ostream &operator<<(std::ostream &os, CharOut manip) {
        os.write(reinterpret_cast<const char *>(&manip.s), sizeof(manip.s));
        return os;
    }

    std::istream &operator>>(std::istream &is, CharIn manip) {
        manip.s = is.get();
        return is;
    }

    CharOut write_char(unsigned char s) { return CharOut(s); }

    CharIn read_char(unsigned char &s) { return CharIn(s); }

    ByteStreamOut::ByteStreamOut(std::ostream &out) : out(out) {}

    void ByteStreamOut::put(bool elem) {
        q.push(elem);
        print_queue();
    }

    void ByteStreamOut::close() {
        if (q.empty()) return;

        while (q.size() < CHAR_BIT) q.push(false);
        print_queue();
    }

    void ByteStreamOut::print_queue() {
        if (q.size() < CHAR_BIT) return;

        unsigned char c = 0;
        for (size_t i = 0; i < CHAR_BIT; i++) {
            c <<= 1;
            c |= q.front();
            q.pop();
        }
        out << write_char(c);
    }

    ByteStreamIn::ByteStreamIn(std::istream &in): in(in) {}

    void ByteStreamIn::get(std::vector<bool> &code) {
        while (q.size() < code.size()) {
            read_char();
        }
        for (size_t i = 0; i < code.size(); i++) {
            code[i] = q.front();
            q.pop();
        }
    }

    void ByteStreamIn::read_char() {
        unsigned char c;
        in >> ::BinManipulator::read_char(c);
        std::vector<bool> byte;
        for (size_t i = 0; i < CHAR_BIT; i++) {
            byte.push_back(c & 1);
            c >>= 1;
        }
        while (!byte.empty()) {
            q.push(byte.back());
            byte.pop_back();
        }
    }

    bool ByteStreamIn::get() {
        if (q.empty()) {
            read_char();
        }
        bool bit = q.front();
        q.pop();
        return bit;
    }

}