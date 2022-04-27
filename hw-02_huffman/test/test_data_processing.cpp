#include "doctest.h"
#include <iostream>
#include <fstream>
#include "reader.h"
#include <climits>
#include <writer.h>
#include <sstream>
#include <vector>

namespace DataProcessing::Test {
    TEST_SUITE("data_reader") {
        TEST_CASE("simple_a") {
            std::stringstream in;
            in << "a";
            Reader dataReader(in);
            CHECK_EQ(dataReader.readBits(CHAR_BIT), 'a');
        }

        TEST_CASE("amount of extracted bytes") {
            std::stringstream in;
            in << "aaa";

            Reader dataReader(in);
            int count = 0;
            while (dataReader.canRead()) {
                CHECK_EQ(count++, dataReader.bytesExtracted());
                dataReader.readBits(CHAR_BIT);
            }

            CHECK_EQ(3, dataReader.bytesExtracted());
        }

        TEST_CASE("empty_file") {
            std::stringstream in;
            Reader dataReader(in);

            CHECK_EQ(false, dataReader.canRead());
            CHECK_EQ(0, dataReader.bytesExtracted());
        }
    }
    TEST_SUITE("data_writer") {
        TEST_CASE("simple_aaa") {
            std::stringstream s;
            Writer writer(s);

            writer.write('a', CHAR_BIT);
            writer.write('a', CHAR_BIT);
            writer.write('a', CHAR_BIT);

            std::string res;
            s >> res;
            CHECK_EQ(res, "aaa");
        }

        TEST_CASE("amount of inserted bytes") {
            std::stringstream s;
            Writer writer(s);

            writer.write(12, 6);
            writer.write(2, 4);
            writer.write(63, 3);

            writer.close();

            CHECK_EQ(writer.bytesInserted(), 2);
        }
    }

    TEST_SUITE("combine") {
        TEST_CASE("small values") {
            std::stringstream s;

            Writer writer(s);
            writer.write(27, 6);
            writer.close();

            Reader reader(s);
            CHECK_EQ(27, reader.readBits(6));
        }

        TEST_CASE("many small values") {
            std::stringstream s;
            std::vector<std::pair<uint8_t, uint8_t>> characters =
                    {{0, 1}, {15, 5}, {1, 1}, {255, 8}, {30, 5}};

            Writer writer(s);
            for (auto p : characters) {
                writer.write(p.first, p.second);
            }
            writer.close();

            Reader reader(s);
            for (auto p : characters) {
                CHECK_EQ(p.first, reader.readBits(p.second));
            }
        }
    }
}