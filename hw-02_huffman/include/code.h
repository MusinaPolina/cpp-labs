#pragma once
#include <cinttypes>
#include <cstddef>

namespace Huffman {
    class Code {
    public:
        Code(uint8_t symbol, size_t length, uint8_t code);
        uint8_t symbol_;
        size_t length_;
        uint8_t code_;

        bool operator<(const Code &a) const;
    };
}
