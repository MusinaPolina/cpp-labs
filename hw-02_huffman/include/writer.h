#pragma once
#include <iostream>
#include <climits>

namespace DataProcessing {
    class Writer {
    public:
        explicit Writer(std::ostream& stream);
        ~Writer();

        void write(uint16_t msg, size_t msg_size);
        void writeInt(uint32_t number);

        int32_t bytesInserted();
        void close();

    private:
        void writeByte();

        size_t buffer_size_ = 0;
        uint32_t buffer_ = 0;
        std::ostream& stream_;
    };

    uint16_t bit_mask(size_t length = CHAR_BIT);
}