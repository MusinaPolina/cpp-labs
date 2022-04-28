#pragma once
#include <cinttypes>
#include <cstddef>

namespace Huffman {
    class Code {
    public:
        Code(uint8_t symbol, size_t length, uint16_t code);
        uint8_t symbol_;
        size_t length_;
        uint16_t code_;

        bool operator<(const Code &a) const;
    };
}
