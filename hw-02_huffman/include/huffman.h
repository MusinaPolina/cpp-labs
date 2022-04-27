#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>

namespace Huffman {
    namespace Exceptions {
        class Exception: public std::exception {
        public:
            [[nodiscard]] virtual const char* what() const noexcept = 0;
        };

        class UnableToOpenFile: public Exception {
        public:
            [[nodiscard]] const char* what() const noexcept override{
                return "Unable to open file";
            }
        };
    }

    class TreeNode {
    public:
        TreeNode(unsigned char c);
        TreeNode(int l, int r);

        unsigned char c = 0;
        int l = -1, r = -1;
        bool is_leaf();

    private:
        bool leaf;
    };

    class NodeCode {
    public:
        unsigned char c;
        std::vector<bool>code;
        NodeCode(unsigned char c, std::vector<bool> code);
    };




}


