#include "code.h"

#include <utility>

namespace Huffman {
    Code::Code(uint8_t symbol): symbol_(symbol) { }
    Code::Code(uint8_t symbol, std::vector<bool> code): symbol_(symbol), code_(std::move(code)) {}

    size_t Code::length() const {
        return code_.size();
    }

    bool Code::operator<(const Code &a) const {
        return symbol_ < a.symbol_;
    }
}
