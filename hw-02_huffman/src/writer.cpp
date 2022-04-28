#include "writer.h"
#include "reader.h"
#include <climits>

namespace DataProcessing {
    Writer::Writer(std::ostream& stream) : stream_(stream) {}

    uint16_t bit_mask(size_t length) {
        return (1 << length) - 1;
    }

    void Writer::writeByte() {
        uint8_t data = (buffer_ & bit_mask());
        if (!stream_.write(reinterpret_cast<char*>(&data), 1)) {
            throw; //TODO()
        }
        buffer_size_ -= CHAR_BIT;
        buffer_ >>= CHAR_BIT;
    }

    void Writer::write(uint16_t msg, size_t msg_size) {
        buffer_ |= ((uint32_t)msg << buffer_size_);
        buffer_size_ += msg_size;

        while (buffer_size_ >= CHAR_BIT) {
            writeByte();
        }
    }

    int32_t Writer::bytesInserted() {
        return stream_.rdbuf()->pubseekoff(0,stream_.cur,stream_.out);
    }

    void Writer::close() {
        while (buffer_size_ >= CHAR_BIT) writeByte();
        if (buffer_size_) writeByte();

        buffer_size_ = 0;
        buffer_ = 0;
    }

    Writer::~Writer() {
        close();
    }

    void Writer::writeInt(uint32_t number) {
        for (size_t i = 0; i < UINT32_WIDTH / CHAR_BIT; i++) {
            write(number & bit_mask(), CHAR_BIT);
            number >>= CHAR_BIT;
        }
    }
}

