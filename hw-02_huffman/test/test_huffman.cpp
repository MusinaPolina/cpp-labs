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



        TEST_CASE("compress") {
            //void compress(DataProcessing::Reader &reader, DataProcessing::Writer &writer, std::vector<Code> &codes);
        }
    }
}