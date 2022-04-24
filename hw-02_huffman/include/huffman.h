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

    class Tree {
    public:
        Tree(std::map<unsigned char, int> ftable);
        Tree(std::vector<NodeCode> codes);

        std::vector<NodeCode> codes;
        std::map<unsigned char, int> code_index_by_char;
        std::map<unsigned char, int> ftable;
        std::vector<TreeNode> tree;
    private:
        void build_code_by_char();
        void build_tree_by_ftable();
        void build_code(TreeNode v, std::vector<bool> code);

        void build_tree_by_codes();
    };

    class Archiver {
    public:
        Archiver(std::string input_name, std::string output_name);
        void compress();
        void decompress();

    private:
        std::map<unsigned char, int> get_ftable();

        size_t put_code(std::ofstream &out, Huffman::Tree tree);
        std::pair<size_t, size_t> put_compressed(std::ofstream &out, Huffman::Tree tree);
        void put_compressed_text(Huffman::Tree tree);


        size_t put_text(Tree tree, size_t stream_lengths, std::ifstream &in);
        std::vector<Huffman::NodeCode> get_code(std::ifstream &in, size_t &size_of_code);

        std::string input_name, output_name;
    };
}


