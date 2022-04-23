#include <iostream>
#include <cassert>
#include <cstring>
#include "huffman.h"

class Query {
public:
    enum class Type {
        compress, decompress
    };

    Type operation;
    std::string input, output;
    Query(int argc, char** argv) {
        assert(argc == 6);
        operation = get_operation_type(argc, argv);
        input = get_input(argc, argv);
        output = get_output(argc, argv);
    }

private:
    void wrong_format() {
        std::cout << "Wrong format";
        exit(0);
    }

    Type get_operation_type(int argc, char** argv) {
        for (size_t i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-u") == 0) {
                return Type::decompress;
            }
            if (strcmp(argv[i], "-c") == 0) {
                return Type::compress;
            }
        }
        wrong_format();
    }

    std::string get_input(int argc, char** argv) {
        for (size_t i = 1; i < argc - 1; i++) {
            if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
                return argv[i + 1];
            }
        }
        wrong_format();
    }

    std::string get_output(int argc, char** argv) {
        for (size_t i = 1; i < argc - 1; i++) {
            if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                return argv[i + 1];
            }
        }
        wrong_format();
    }
};


int main(int argc, char** argv) {
    Query query(argc, argv);
    Huffman::Archiver archiver(query.input, query.output);
    if (query.operation == Query::Type::compress) {
        archiver.compress();
    } else {
        archiver.decompress();
    }
    return 0;
}