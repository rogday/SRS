#pragma once

#include <cstdint>
#include <iostream>
#include <random>
#include <tuple>

class Treap {
    struct Node {
        Node(std::uint64_t val)
            : p(rand(engine)), val(val), left(nullptr), right(nullptr) {}
        std::uint64_t p;
        std::uint64_t val;

        Node *left;
        Node *right;

        // utility
        static std::random_device rd;
        static std::default_random_engine engine;
        static std::uniform_int_distribution<std::uint64_t> rand;
    };

    Node *root;

  private:
    std::pair<Node *, Node *> split(Node *, std::uint64_t);
    Node *merge(Node *, Node *);
    void remove(Node *&, std::uint64_t);
    bool search(Node *, std::uint64_t);

    void print(Node *);

  public:
    Treap() : root(nullptr) {}

    void insert(std::uint64_t);
    void remove(std::uint64_t val) { remove(root, val); }
    bool search(std::uint64_t val) { return search(root, val); }

    void print() {
        print(root);
        std::cout << std::endl;
    }
};