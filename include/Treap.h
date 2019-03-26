#pragma once

#include <cstdint>
#include <iostream>
#include <random>
#include <tuple>

#include <utility.h>

template <class T> class Treap {
  struct Node {
    Node(T val)
        : p(utility::get_random()), val(val), left(nullptr), right(nullptr) {}
    ~Node() {
      delete left;
      delete right;
    }
    std::uint64_t p;
    T val;

    Node *left;
    Node *right;
  };

  Node *root;

private:
  std::pair<Node *, Node *> split(Node *ptr, T val) {
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

  bool search(Node *ptr, T val) {
    if (!ptr)
      return false;

    if (val == ptr->val)
      return true;

    if (val > ptr->val)
      return search(ptr->right, val);
    return search(ptr->left, val);
  };

  void erase(Node *&ptr, T val) {
    if (!ptr)
      return;

    if (val == ptr->val) {
      Node *tmp = ptr;
      ptr = merge(ptr->left, ptr->right);
      tmp->left = tmp->right = nullptr;
      delete tmp;
      return;
    }

    if (val > ptr->val)
      erase(ptr->right, val);
    else
      erase(ptr->left, val);
  }

  void print(Node *ptr) {
    if (!ptr)
      return;

    print(ptr->left);
    std::cout << (ptr->val) << " ";
    print(ptr->right);
  }

public:
  Treap() : root(nullptr) {}
  ~Treap() { delete root; }

  void insert(T val) {
    Node *newNode = new Node(val);
    auto t = split(root, val);
    t.first = merge(t.first, newNode);
    root = merge(t.first, t.second);
  }

  void erase(T val) { erase(root, val); }

  bool find(T val) { return search(root, val); }

  void print() {
    print(root);
    std::cout << std::endl;
  }
};