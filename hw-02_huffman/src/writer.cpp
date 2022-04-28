#include "writer.h"
#include "reader.h"
#include <climits>
#include <algorithm>

namespace DataProcessing {
    Writer::Writer(std::ostream& stream) : stream_(stream) {}



    bool Writer::writeByte() {
        if (buffer_.size() < CHAR_BIT) {
            return false;
        }

        uint8_t byte = 0;
        for (size_t i = 0; i < CHAR_BIT; i++) {
            byte <<= 1;
            byte |= buffer_.front();
            buffer_.pop();
        }
        if (!stream_.write(reinterpret_cast<char*>(&byte), 1)) {
            throw; //TODO()
        }
        return true;
    }

    void Writer::writeBit(bool bit) {
        buffer_.push(bit);
        writeByte();
    }

    void Writer::writeBits(const std::vector<bool>& bits) {
        for (bool bit: bits) {
            writeBit(bit);
        }
    }

    void Writer::writeBits(uint32_t bits, size_t length) {
        std::vector<bool> bits_vector;
        for (size_t i = 0; i < length; i++) {
            bits_vector.push_back(bits & 1);
            bits >>= 1;
        }
        std::reverse(bits_vector.begin(), bits_vector.end());
        writeBits(bits_vector);
    }

    void Writer::writeBits(uint8_t byte) {
        writeBits(byte, CHAR_BIT);
    }

    int32_t Writer::bytesInserted() {
        return stream_.rdbuf()->pubseekoff(0,stream_.cur,stream_.out);
    }

    void Writer::close() {
        while (writeByte());
        if (!buffer_.empty()) {
            while (buffer_.size() < CHAR_BIT) {
                buffer_.push(false);
            }
            writeByte();
        }
    }

    Writer::~Writer() {
        close();
    }

    uint32_t bit_mask(size_t length) {
        return (1 << length) - 1;
    }

    void Writer::writeInt(uint32_t number) {
        writeBits(number, UINT32_WIDTH);
    }
}

