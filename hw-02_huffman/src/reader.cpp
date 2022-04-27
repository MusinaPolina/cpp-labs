#include "reader.h"
#include "writer.h"
#include <climits>

namespace DataProcessing {
    Reader::Reader(std::istream &stream): stream_(stream) {
        stream_.seekg(0, std::istream::beg);
    }

    void Reader::ReadByte() {
        uint8_t byte;
        if (!stream_.read(reinterpret_cast<char*>(&byte), 1)) {
            throw;//TODO()
        }
        buffer_ |= ((uint16_t)byte << buffer_size_);
        buffer_size_ += CHAR_BIT;
    }

    uint8_t Reader::readBits(size_t count) {
        if (count > CHAR_BIT) throw; //TODO()

        while (buffer_size_ < count) {
            ReadByte();
        }

        buffer_size_ -= count;
        uint8_t result = buffer_ & bit_mask(count);
        buffer_ >>= count;

        return result;
    }

    bool Reader::canRead() {
        if (buffer_size_) return true;
        return stream_.peek() != EOF;
    }

    uint32_t Reader::bytesExtracted() {
        if (stream_.tellg() == -1) {
            stream_.clear();
            stream_.seekg(0, std::istream::end);
            return stream_.tellg();
        }
        return stream_.tellg();
    }

    uint32_t Reader::readInt() {
        uint32_t reversed = 0;
        for (size_t i = 0; i < UINT32_WIDTH / CHAR_BIT; i++) {
            uint8_t current = readBits(CHAR_BIT);
            reversed <<= CHAR_BIT;
            reversed |= current;
        }
        uint32_t result = 0;
        for (size_t i = 0; i < UINT32_WIDTH / CHAR_BIT; i++) {
            result <<= CHAR_BIT;
            result |= reversed & bit_mask();
            reversed >>= CHAR_BIT;
        }
        return result;
    }
}