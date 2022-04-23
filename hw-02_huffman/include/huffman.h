#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <deque>
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
        TreeNode(TreeNode *l, TreeNode *r);

        unsigned char c = 0;
        TreeNode *l = nullptr, *r = nullptr;
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
        void build_code(TreeNode *v, std::vector<bool> code);

        void build_tree_by_codes();
    };

    class Archiver {
    public:
        Archiver(std::string input_name, std::string output_name);
        void compress();
        void decompress();

    private:
        std::map<unsigned char, int> get_ftable();

        void put_code(std::ofstream &out, Huffman::Tree tree);
        void put_compressed(std::ofstream &out, Huffman::Tree tree);
        void put_compressed_text(Huffman::Tree tree);


        void put_text(Tree tree, size_t stream_lengths, std::ifstream &in);
        std::vector<Huffman::NodeCode> get_code(std::ifstream &in);

        std::string input_name, output_name;
    };
}


