#include <cstring>
#include "bin_manip.h"

BinManipulatorIntOut::BinManipulatorIntOut(const int32_t &x): x(x) {}
BinManipulatorIntIn::BinManipulatorIntIn(int32_t &x): x(x) {}

std::ostream &operator<<(std::ostream &os, BinManipulatorIntOut manip) {
    return os.write(reinterpret_cast<const char *>(&manip.x), sizeof(manip.x));
}

std::istream &operator>>(std::istream &is, BinManipulatorIntIn manip) {
    return is.read(reinterpret_cast<char *>(&manip.x), sizeof(manip.x));
}

BinManipulatorIntOut write_le_int32(const int32_t &x) { return BinManipulatorIntOut(x); }
BinManipulatorIntIn read_le_int32(int32_t &x) { return BinManipulatorIntIn(x); }


BinManipulatorBoolOut::BinManipulatorBoolOut(const bool &x): x(x) {}
BinManipulatorBoolIn::BinManipulatorBoolIn(bool &x): x(x) {}

std::ostream &operator<<(std::ostream &os, BinManipulatorBoolOut manip) {
    return os.write(reinterpret_cast<const char *>(&manip.x), sizeof(manip.x));
}

std::istream &operator>>(std::istream &is, BinManipulatorBoolIn manip) {
    return is.read(reinterpret_cast<char *>(&manip.x), sizeof(manip.x));
}

BinManipulatorBoolOut write_bool(const bool &x) { return BinManipulatorBoolOut(x); }
BinManipulatorBoolIn read_bool(bool &x) { return BinManipulatorBoolIn(x); }


BinManipulatorCharOut::BinManipulatorCharOut(const char *s, size_t sz): s(s), sz(sz) {}
BinManipulatorCharIn::BinManipulatorCharIn(char *s, size_t sz): s(s), sz(sz) {}

std::ostream &operator<<(std::ostream &os, BinManipulatorCharOut manip) {
    for (size_t i = 0; i <= manip.sz; i++) {
        os.write(reinterpret_cast<const char *>(&manip.s[i]), sizeof(manip.s[i]));
        if (manip.s[i] == 0) {
            return os;
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, BinManipulatorCharIn manip) {
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

BinManipulatorCharOut write_c_str(const char* s) { return BinManipulatorCharOut(s, strlen(s)); }
BinManipulatorCharIn read_c_str(char* s, size_t sz) { return BinManipulatorCharIn(s, sz); }

