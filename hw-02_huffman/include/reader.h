#pragma once
#include <iostream>
#include <queue>

namespace DataProcessing {
    class Reader {
    public:
        explicit Reader(std::istream& stream);

        uint8_t readBits(size_t count);
        bool readBit();

        uint32_t readInt();

        bool canRead();
        uint32_t bytesExtracted();

        void close();
    private:
        bool readByte();
        std::queue<bool> buffer_;

        std::istream& stream_;
    };

    bool reverseChar(uint8_t bit, size_t i);
    uint32_t reverse(uint32_t x, size_t length);
}