#include <map>
#include <queue>
#include <utility>
#include "huffman.h"
#include "bin_manip.h"


namespace Huffman {
    TreeNode::TreeNode(unsigned char c): c(c), leaf(true) {}

    TreeNode::TreeNode(TreeNode *l, TreeNode *r): l(l), r(r), leaf(false) {}

    bool TreeNode::is_leaf() { return leaf; }

    NodeCode::NodeCode(unsigned char c, std::vector<bool> deq): c(c), code(std::move(deq)) {}

    Tree::Tree(std::map<unsigned char, int> ftable): ftable(std::move(ftable)) {
        build_tree_by_ftable();
        build_code(&tree.back(), {});
        build_code_by_char();
    }

    void Tree::build_code_by_char() {
        for (size_t i = 0; i < codes.size(); i++) {
            code_index_by_char[codes[i].c] = i;
        }
    }

    void Tree::build_tree_by_ftable() {
        if (ftable.empty()) {
            return;
        }
        std::priority_queue<std::pair<int, size_t>> q;
        for (auto [c, frequency] : ftable) {
            q.push(std::make_pair(frequency, tree.size()));
            tree.emplace_back(c);
        }
        while (q.size() > 1) {
            auto [a_freq, a] = q.top();
            q.pop();
            auto [b_freq, b] = q.top();
            q.pop();
            q.push(std::make_pair(a_freq + b_freq, tree.size()));
            tree.emplace_back(&tree[a], &tree[b]);
        }
    }

    void Tree::build_code(TreeNode *v, std::vector<bool> code) {
        if (v->is_leaf()) {
            if (code.empty()) code.push_back(false);
            codes.emplace_back(v->c, code);
            return;
        }
        code.push_back(false);
        build_code(v->l, code);
        code.pop_back();
        code.push_back(true);
        build_code(v->r, code);
    }

    Tree::Tree(std::vector<NodeCode> codes): codes(std::move(codes)) {
        build_tree_by_codes();
    };

    void Tree::build_tree_by_codes() {
        if (codes.size() == 1) {
            tree.emplace_back(codes.front().c);
            tree[0].l = tree[0].r = &tree[0];
            return;
        }
        tree.emplace_back(nullptr, nullptr);
        for (auto code: codes) {
            TreeNode *cur = &tree[0];
            for (size_t i = 0; i < code.code.size(); i++) {
                auto bit = code.code[i];
                TreeNode *nxt = bit ? cur->r : cur->l;
                if (!nxt) {
                    if (i + 1 == code.code.size()) tree.emplace_back(code.c);
                    else tree.emplace_back(nullptr, nullptr);
                    nxt = &tree.back();
                    bit ? cur-> r = nxt : cur->l = nxt;
                }
                cur = nxt;
            }
            cur->l = cur->r = &tree[0];
        }
    }

    Archiver::Archiver(std::string  input_name, std::string  output_name):
            input_name(std::move(input_name)), output_name(std::move(output_name)) {};

    void Archiver::compress() {
        std::map<unsigned char, int> ftable = get_ftable();
        Tree tree = Huffman::Tree(ftable);
        put_compressed_text(tree);
    }

    void Archiver::put_compressed_text(Huffman::Tree tree) {
        std::ofstream out(output_name, std::ios::binary);

        if (out.fail()) throw Exceptions::UnableToOpenFile();

        put_code(out, tree);
        put_compressed(out, tree);

        out.close();
    }

    std::map<unsigned char, int> Archiver::get_ftable() {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        std::map<unsigned char, int> ftable;
        while (in) {
            char c;
            in.read(&c, sizeof(char));
            ftable[c]++;
        }

        in.close();

        return ftable;
    }

    void Archiver::put_code(std::ofstream &out, Huffman::Tree tree) {
        auto codes = tree.codes;
        out << BinManipulator::write_le_int32(codes.size());
        size_t stream_length = 0;
        for (auto node: codes) {
            out << BinManipulator::write_char(node.c);
            out << BinManipulator::write_le_int32(node.code.size());
            stream_length += node.code.size() * tree.ftable[node.c];
        }
        BinManipulator::ByteStreamOut stream(out);
        for (auto node: codes) {
            for (auto a : node.code) {
                stream.put(a);
            }
        }
        stream.close();
        out << BinManipulator::write_le_int32(stream_length);
    }

    void Archiver::put_compressed(std::ofstream &out, Huffman::Tree tree) {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        BinManipulator::ByteStreamOut stream(out);
        while (in) {
            char c;
            in.read(&c, sizeof(char));
            for (auto bit: tree.codes[tree.code_index_by_char[c]].code) {
                stream.put(bit);
            }
        }
        stream.close();

        in.close();
    }

    void Archiver::decompress() {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        std::vector<Huffman::NodeCode> codes = get_code(in);
        int32_t stream_lengths;
        in >> BinManipulator::read_le_int32(stream_lengths);
        Huffman::Tree tree = Huffman::Tree(codes);
        put_text(tree, stream_lengths, in);

        in.close();
    }

    void Archiver::put_text(Tree tree, size_t stream_lengths, std::ifstream &in) {
        std::ofstream out(output_name, std::ios::binary);

        if (out.fail()) throw Exceptions::UnableToOpenFile();

        BinManipulator::ByteStreamIn stream(in);

        Huffman::TreeNode *cur = &tree.tree.front();
        for (size_t i = 0; i < stream_lengths; i++) {
            bool bit = stream.get();
            cur = bit ? cur->r : cur->l;
            if (cur == nullptr) {
                std::cout << "(((";
                exit(0);
            }
            if (cur->is_leaf()) {
                out << BinManipulator::write_char(cur->c);
            }
        }

        out.close();
    }

    std::vector<Huffman::NodeCode> Archiver::get_code(std::ifstream &in) {
        int32_t number;
        in >> BinManipulator::read_le_int32(number);

        std::vector<Huffman::NodeCode> codes;
        for (size_t i = 0; i < number; i++) {
            unsigned char c;
            int32_t bits;
            in >> BinManipulator::read_char(c) >> BinManipulator::read_le_int32(bits);
            codes.emplace_back(c, std::vector<bool>(bits));
        }
        BinManipulator::ByteStreamIn stream(in);
        for (size_t i = 0; i < number; i++) {
            stream.get(codes[i].code);
        }
        return codes;
    }
}
