#pragma once
#include <iostream>

namespace DataProcessing {
    class Reader {
    public:
        explicit Reader(std::istream& stream);

        uint16_t readBits(size_t count);
        bool canRead();
        int32_t bytesExtracted();
    private:
        void ReadByte();

        size_t buffer_size_ = 0;
        uint16_t buffer_ = 0;

        std::istream& stream_;
    };
}