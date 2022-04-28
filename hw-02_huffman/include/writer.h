#pragma once
#include <iostream>
#include <climits>
#include <queue>

namespace DataProcessing {
    class Writer {
    public:
        explicit Writer(std::ostream& stream);
        ~Writer();

        void writeBits(const std::vector<bool>& bits);
        void writeBits(uint32_t bits, size_t length);
        void writeBits(uint8_t byte);
        void writeBit(bool bit);
        void writeInt(uint32_t number);

        int32_t bytesInserted();
        void close();

    private:
        bool writeByte();

        std::queue<bool> buffer_;
        std::ostream& stream_;
    };

    //uint32_t bit_mask(size_t length = CHAR_BIT);
}