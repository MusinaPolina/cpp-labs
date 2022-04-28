#pragma once
#include <cinttypes>
#include <cstddef>
#include <vector>

namespace Huffman {
    class Code {
    public:
        Code(uint8_t symbol, std::vector<bool> code);
        explicit Code(uint8_t symbol);

        uint8_t symbol_;
        std::vector<bool> code_;

        [[nodiscard]] size_t length() const;
        bool operator<(const Code &a) const;
    };
}
