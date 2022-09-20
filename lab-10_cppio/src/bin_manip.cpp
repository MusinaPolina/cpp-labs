#include <cstring>
#include "bin_manip.h"


BinManipulator::IntOut::IntOut(const int32_t &x): x(x) {}
BinManipulator::IntIn::IntIn(int32_t &x): x(x) {}


std::ostream &BinManipulator::operator<<(std::ostream &os, IntOut manip) {
    return os.write(reinterpret_cast<const char *>(&manip.x), sizeof(manip.x));
}

std::istream &BinManipulator::operator>>(std::istream &is, IntIn manip) {
    return is.read(reinterpret_cast<char *>(&manip.x), sizeof(manip.x));
}

BinManipulator::IntOut BinManipulator::write_le_int32(const int32_t &x) { return IntOut(x); }
BinManipulator::IntIn BinManipulator::read_le_int32(int32_t &x) { return IntIn(x); }


BinManipulator::BoolOut::BoolOut(bool x): x(x) {}
BinManipulator::BoolIn::BoolIn(bool &x): x(x) {}

std::ostream &BinManipulator::operator<<(std::ostream &os, BoolOut manip) {
    return os.write(reinterpret_cast<const char *>(&manip.x), sizeof(manip.x));
}

std::istream &BinManipulator::operator>>(std::istream &is, BoolIn manip) {
    return is.read(reinterpret_cast<char *>(&manip.x), sizeof(manip.x));
}

BinManipulator::BoolOut BinManipulator::write_bool(bool x) { return BoolOut(x); }
BinManipulator::BoolIn BinManipulator::read_bool(bool &x) { return BoolIn(x); }


BinManipulator::CharOut::CharOut(const char *s, size_t sz): s(s), sz(sz) {}
BinManipulator::CharIn::CharIn(char *s, size_t sz): s(s), sz(sz) {}

std::ostream &BinManipulator::operator<<(std::ostream &os, CharOut manip) {
    for (size_t i = 0; i <= manip.sz; i++) {
        os.write(reinterpret_cast<const char *>(&manip.s[i]), sizeof(manip.s[i]));
        if (manip.s[i] == 0) {
            return os;
        }
    }
    return os;
}

std::istream &BinManipulator::operator>>(std::istream &is, CharIn manip) {
    for (size_t i = 0; i < manip.sz; i++) {
        manip.s[i] = 0;
    }
    for (size_t i = 0; i < manip.sz; i++) {
        is.read(reinterpret_cast<char *>(&manip.s[i]), sizeof(manip.s[i]));
        if (manip.s[i] == 0) {
            is.clear();
            return is;
        }
    }
    return is;
}

BinManipulator::CharOut BinManipulator::write_c_str(const char* s) { return CharOut(s, strlen(s)); }
BinManipulator::CharIn BinManipulator::read_c_str(char* s, size_t sz) { return CharIn(s, sz); }

