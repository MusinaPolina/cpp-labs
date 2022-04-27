#include "tree.h"
#include <vector>
#include <queue>
#include <algorithm>

namespace Huffman {

    Tree::Tree(std::map<uint16_t, uint32_t> frequency_table) {
        if (frequency_table.empty()) return;
        for (uint8_t t = 0; frequency_table.size() == 1; t++) frequency_table[t]++;

        auto compare = [](Node* l, Node* r) {return *l < *r; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> priorities(compare);

        for (auto p : frequency_table) {
            Node *node = new Node(p.first, p.second);
            priorities.push(node);
        }

        while (priorities.size() > 1) {
            Node *a = priorities.top();
            priorities.pop();
            Node *b = priorities.top();
            priorities.pop();

            Node *c = new Node(a, b);
            priorities.push(c);
        }

        root_ = priorities.top();
    }

    Tree::~Tree() {
        delete root_;
    }

    void Tree::DFS(std::vector<Code>& codes, Node* node, size_t length, int8_t code) {
        if (!node) return;
        if (node->isLeaf()) {
            codes.emplace_back(node->symbol_, length, code);
            return;
        }
        DFS(codes, node->left_, length + 1, code << 1);
        DFS(codes, node->right_, length + 1, (code << 1) + 1);
    }

    std::vector<Code> Tree::getCodes() {
        std::vector<Code> codes;
        DFS(codes, root_);
        return codes;
    }

    Tree::Tree(const std::vector<Code> &codes) {
        root_ = new Node();
        for (auto code: codes) {
            addCode(code);
        }
    }

    void Tree::addCode(const Code &code) {
        Node* node = root_;
        for (size_t i = 0; i < code.length_; i++) {
            bool path = code.code_ & (1 << i);
            auto &nxt = path ? node->right_ : node->left_;
            if (nxt == nullptr) {
                Node* c = new Node();
                nxt = c;
            }
            node = nxt;
        }
        node->symbol_ = code.symbol_;
    }

    uint8_t Tree::getSymbol(DataProcessing::Reader& reader) {
        Node* node = root_;
        while (!node->isLeaf()) {
            bool path = reader.readBits(1);
            node = path ? node->right_ : node->left_;
        }
        return node->symbol_;
    }
}