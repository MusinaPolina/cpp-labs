#include "code.h"

namespace Huffman {
    Code::Code(uint8_t symbol, size_t length, uint8_t code): symbol_(symbol), length_(length), code_(code) {}

    bool Code::operator<(const Code &a) const {
        return symbol_ < a.symbol_;
    }
}
