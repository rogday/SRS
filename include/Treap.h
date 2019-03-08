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
  std::pair<Node *, Node *> split(Node *ptr, std::uint64_t val) {
    if (!ptr)
      return {nullptr, nullptr};

    if (val > ptr->val) {
      auto tmp = split(ptr->right, val);
      ptr->right = tmp.first;
      return {ptr, tmp.second};
    } else {
      auto tmp = split(ptr->left, val);
      ptr->left = tmp.second;
      return {tmp.first, ptr};
    }
  }

  Node *merge(Node *t1, Node *t2) {
    if (!t2)
      return t1;

    if (!t1)
      return t2;

    if (t1->p > t2->p) {
      t1->right = merge(t1->right, t2);
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
      return t2;
    }
  }

  void print(Node *ptr) {
    if (!ptr)
      return;

    print(ptr->left);
    std::cout << (ptr->val) << " ";
    print(ptr->right);
  }

  void remove(Node *&ptr, std::uint64_t val) {
    if (!ptr)
      return;

    if (val == ptr->val) {
      Node *tmp = ptr;
      ptr = merge(ptr->left, ptr->right);
      delete tmp;
      return;
    }

    if (val > ptr->val)
      remove(ptr->right, val);
    else
      remove(ptr->left, val);
  }

public:
  Treap() : root(nullptr) {}

  void insert(std::uint64_t val) {
    Node *newNode = new Node(val);
    auto t = split(root, val);
    t.first = merge(t.first, newNode);
    root = merge(t.first, t.second);
  }

  void remove(std::uint64_t val) { remove(root, val); }

  void print() {
    print(root);
    std::cout << std::endl;
  }
};