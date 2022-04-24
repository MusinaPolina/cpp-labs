#include <map>
#include <queue>
#include <utility>
#include "huffman.h"
#include "bin_manip.h"


namespace Huffman {
    TreeNode::TreeNode(unsigned char c): c(c), leaf(true) {}

    TreeNode::TreeNode(int l, int r): l(l), r(r), leaf(false) {}

    bool TreeNode::is_leaf() { return leaf; }

    NodeCode::NodeCode(unsigned char c, std::vector<bool> deq): c(c), code(std::move(deq)) {}

    Tree::Tree(std::map<unsigned char, int> ftable): ftable(std::move(ftable)) {
        build_tree_by_ftable();
        build_code(tree.back(), {});
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
            tree.emplace_back(a, b);
        }
    }

    void Tree::build_code(TreeNode v, std::vector<bool> code) {
        if (v.is_leaf()) {
            if (code.empty()) code.push_back(false);
            codes.emplace_back(v.c, code);
            return;
        }
        code.push_back(false);
        build_code(tree[v.l], code);
        code.pop_back();
        code.push_back(true);
        build_code(tree[v.r], code);
    }

    Tree::Tree(std::vector<NodeCode> codes): codes(std::move(codes)) {
        build_tree_by_codes();
    };

    void Tree::build_tree_by_codes() {
        if (codes.size() == 1) {
            tree.emplace_back(codes.front().c);
            tree[0].l = tree[0].r = 0;
            return;
        }
        tree.emplace_back(-1, -1);
        for (auto code: codes) {
            int cur = 0;
            for (size_t i = 0; i < code.code.size(); i++) {
                bool bit = code.code[i];
                int nxt = bit ? tree[cur].r : tree[cur].l;
                if (nxt == -1) {
                    if (i + 1 == code.code.size()) tree.emplace_back(code.c);
                    else tree.emplace_back(-1, -1);
                    nxt = tree.size() - 1;
                    bit ? tree[cur].r = nxt : tree[cur].l = nxt;
                }
                cur = nxt;
            }
            tree[cur].l = tree[cur].r = 0;
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

        size_t size_of_code = put_code(out, tree);
        auto [size_of_text, initial_size] = put_compressed(out, tree);

        out.close();

        std::cout << initial_size << '\n' << size_of_text << '\n' << size_of_code << '\n';
    }

    std::map<unsigned char, int> Archiver::get_ftable() {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        std::map<unsigned char, int> ftable;
        while (in) {
            unsigned char c;
            in >> BinManipulator::read_char(c);
            ftable[c]++;
        }

        in.close();

        return ftable;
    }

    size_t Archiver::put_code(std::ofstream &out, Huffman::Tree tree) {
        size_t size_of_code = 0;

        auto codes = tree.codes;

        out << BinManipulator::write_le_int32(codes.size());
        size_of_code += sizeof(int32_t);

        size_t stream_length = 0;

        for (auto node: codes) {

            out << BinManipulator::write_char(node.c);
            size_of_code += sizeof(unsigned char);

            out << BinManipulator::write_le_int32(node.code.size());
            size_of_code += sizeof(int32_t);

            stream_length += node.code.size() * tree.ftable[node.c];
        }

        BinManipulator::ByteStreamOut stream(out);
        for (auto node: codes) {
            for (auto a : node.code) {
                stream.put(a);
            }
        }
        stream.close();
        size_of_code += stream_length / 4 + bool(stream_length % 4);

        out << BinManipulator::write_le_int32(stream_length);
        size_of_code += sizeof(int32_t);

        return size_of_code;
    }

    std::pair<size_t, size_t> Archiver::put_compressed(std::ofstream &out, Huffman::Tree tree) {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        size_t size_of_text = 0, initial_size = 0;

        BinManipulator::ByteStreamOut stream(out);
        while (in) {
            unsigned char c;

            in >> BinManipulator::read_char(c);
            initial_size += 1;

            size_of_text += tree.codes[tree.code_index_by_char[c]].code.size();
            for (auto bit: tree.codes[tree.code_index_by_char[c]].code) {
                stream.put(bit);
            }
        }
        stream.close();

        size_of_text = (size_of_text / 4) + bool(size_of_text % 4);

        in.close();
        return {size_of_text, initial_size};
    }

    void Archiver::decompress() {
        std::ifstream in(input_name, std::ios::binary);

        if (in.fail()) throw Exceptions::UnableToOpenFile();

        size_t size_of_code = sizeof(int32_t);
        std::vector<Huffman::NodeCode> codes = get_code(in, size_of_code);

        int32_t stream_lengths;
        in >> BinManipulator::read_le_int32(stream_lengths);

        Huffman::Tree tree = Huffman::Tree(codes);
        size_t initial_size = put_text(tree, stream_lengths, in);

        in.close();
        size_t size_of_text = stream_lengths / 4 + bool(stream_lengths % 4);
        std::cout << size_of_text << '\n' << initial_size  << '\n' << size_of_code << '\n';
    }

    size_t Archiver::put_text(Tree tree, size_t stream_lengths, std::ifstream &in) {
        std::ofstream out(output_name, std::ios::binary);

        if (out.fail()) throw Exceptions::UnableToOpenFile();

        BinManipulator::ByteStreamIn stream(in);
        size_t initial_size = 0;

        int cur = 0;
        for (size_t i = 0; i < stream_lengths; i++) {
            bool bit = stream.get();
            cur = bit ? tree.tree[cur].r : tree.tree[cur].l;
            if (cur == -1) {
                std::cout << "(((";
                exit(0);
            }
            if (tree.tree[cur].is_leaf()) {
                out << BinManipulator::write_char(tree.tree[cur].c);
                initial_size += sizeof(unsigned char);

                cur = 0;
            }
        }

        out.close();
        return initial_size;
    }

    std::vector<Huffman::NodeCode> Archiver::get_code(std::ifstream &in, size_t &size_of_code) {

        int32_t number;
        in >> BinManipulator::read_le_int32(number);
        size_of_code += sizeof(int32_t);

        std::vector<Huffman::NodeCode> codes;
        for (size_t i = 0; i < number; i++) {
            unsigned char c;
            int32_t bits;
            in >> BinManipulator::read_char(c);
            size_of_code += sizeof(unsigned char);
            in >> BinManipulator::read_le_int32(bits);
            size_of_code += sizeof(int32_t);

            codes.emplace_back(c, std::vector<bool>(bits));
        }
        BinManipulator::ByteStreamIn stream(in);
        size_t sum = 0;
        for (size_t i = 0; i < number; i++) {
            stream.get(codes[i].code);
            sum += codes[i].code.size();
        }
        size_of_code += sum / 4 + bool(sum % 4);

        return codes;
    }
}
