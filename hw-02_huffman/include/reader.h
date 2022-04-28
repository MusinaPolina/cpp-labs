#pragma once
#include <iostream>

namespace DataProcessing {
    class Reader {
    public:
        explicit Reader(std::istream& stream);

        uint16_t readBits(size_t count);
        uint32_t readInt();
        bool canRead();
        uint32_t bytesExtracted();

        void close();
    private:
        void ReadByte();

        size_t buffer_size_ = 0;
        uint32_t buffer_ = 0;

        std::istream& stream_;
    };

    uint32_t reverse(uint32_t x, size_t length);
}