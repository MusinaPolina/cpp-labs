#include "reader.h"
#include <climits>

namespace DataProcessing {
    Reader::Reader(std::istream &stream): stream_(stream) {}

    void Reader::ReadByte() {
        uint16_t byte;
        if (!stream_.read(reinterpret_cast<char*>(&byte), 1)) {
            throw;//TODO()
        }
        buffer_ += (byte << buffer_size_);
        buffer_size_ += CHAR_BIT;
    }

    uint16_t Reader::readBits(size_t count) {
        if (count > CHAR_BIT) throw; //TODO()

        while (buffer_size_ < count) {
            ReadByte();
        }

        buffer_size_ -= count;
        uint16_t result = buffer_ & ((1 << count) - 1);
        buffer_ >>= count;

        return result;
    }

    bool Reader::canRead() {
        if (buffer_size_) return true;
        return stream_.peek() != EOF;
    }

    int32_t Reader::bytesExtracted() {
        return stream_.rdbuf()->pubseekoff(0,stream_.cur,stream_.out);
    }
}