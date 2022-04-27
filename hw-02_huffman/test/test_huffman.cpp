#include "doctest.h"

#include <iostream>
#include <sstream>
#include "archiver.h"
#include "tree.h"
#include "code.h"

namespace Huffman::Test {
    TEST_SUITE("archiver") {
        TEST_CASE("buildFrequencyTable") {
            std::stringstream stream;
            std::string s = "a\\bs\n#$$$\n";
            stream << s;
            std::map<uint16_t, uint32_t> table;
            uint32_t length = buildFrequencyTable(stream, table);

            CHECK_EQ(length, s.length());
            CHECK_EQ(table.size(), 7);
            CHECK_EQ(table['\n'], 2);
            CHECK_EQ(table['\\'], 1);
            CHECK_EQ(table['$'], 3);
        }

        TEST_CASE("build tree") {
            std::stringstream stream;
            std::string s = "bbbb  c";
            stream << s;
            std::map<uint16_t, uint32_t> table;
            uint32_t length = buildFrequencyTable(stream, table);
            Tree tree(table);
            std::vector<Code> codes = tree.getCodes();

            CHECK_EQ(codes.size(), 3);

            CHECK_EQ(codes[0].symbol_, 'c');
            CHECK_EQ(codes[0].length_, 2);
            CHECK_EQ(codes[0].code_, 0);

            CHECK_EQ(codes[1].symbol_, ' ');
            CHECK_EQ(codes[1].length_, 2);
            CHECK_EQ(codes[1].code_, 1);

            CHECK_EQ(codes[2].symbol_, 'b');
            CHECK_EQ(codes[2].length_, 1);
            CHECK_EQ(codes[2].code_, 1);
        }

        TEST_CASE("writeInfo small") {
            //void writeInfo(DataProcessing::Writer &writer, int32_t extracted, std::vector<Code> &codes);
            std::stringstream stream;
            std::string s = "55";
            stream << s;
            std::map<uint16_t, uint32_t> table;
            uint32_t length = buildFrequencyTable(stream, table);
            Tree tree(table);
            std::vector<Code> codes = tree.getCodes();

            std::stringstream output;
            DataProcessing::Writer writer(output);
            writeInfo(writer, length, codes);
            writer.close();

            std::vector<uint32_t> result = {0, 1, 0, 53, 1, 1};
            DataProcessing::Reader reader(output);

            CHECK_EQ(2, reader.readInt());
            for (int i = 0; i < result.size(); i += 3) {
                CHECK_EQ(result[i], reader.readBits(CHAR_BIT));
                CHECK_EQ(result[i + 1], reader.readInt());
                CHECK_EQ(result[i + 2], reader.readBits(result[i + 1]));
            }
            CHECK_EQ(2, reader.readInt());
        }

        TEST_CASE("writeInfo medium") {
            std::stringstream stream;
            std::string s = "aa\n3333_55";
            stream << s;
            std::map<uint16_t, uint32_t> table;
            uint32_t length = buildFrequencyTable(stream, table);
            Tree tree(table);
            std::vector<Code> codes = tree.getCodes();

            std::stringstream output;
            DataProcessing::Writer writer(output);
            writeInfo(writer, length, codes);
            writer.close();

            std::vector<uint32_t> result = {53, 2, 0, 97, 2, 1, 10, 3, 4, 95, 3, 5, 51, 2, 3};
            DataProcessing::Reader reader(output);

            CHECK_EQ(5, reader.readInt());
            for (int i = 0; i < result.size(); i += 3) {
                CHECK_EQ(result[i], reader.readBits(CHAR_BIT));
                CHECK_EQ(result[i + 1], reader.readInt());
                CHECK_EQ(result[i + 2], reader.readBits(result[i + 1]));
            }
            CHECK_EQ(10, reader.readInt());
        }

        TEST_CASE("compress") {
            //void compress(DataProcessing::Reader &reader, DataProcessing::Writer &writer, std::vector<Code> &codes);
        }
    }
}