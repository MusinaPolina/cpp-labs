#pragma once
#include <iostream>

namespace DataProcessing {
    class Writer {
    public:
        explicit Writer(std::ostream& stream);
        ~Writer();

        void write(uint16_t msg, size_t msg_size);
        int32_t bytesInserted();
        void close();

    private:
        void writeByte();

        size_t buffer_size_ = 0;
        uint16_t buffer_ = 0;
        std::ostream& stream_;
    };
}