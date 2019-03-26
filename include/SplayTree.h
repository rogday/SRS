#pragma once

#include <iostream>

template <class T> class SplayTree {
  struct Node {
    T value;
    Node *left, *right, *parent;

    Node() : left(nullptr), right(nullptr), parent(nullptr) {}

    ~Node() {
      delete left;
      delete right;
    }

    void setL(Node *L) {
      left = L;
      if (left)
        left->parent = this;
    }
    void setR(Node *R) {
      right = R;
      if (right)
        right->parent = this;
    }
  };

  Node *root = nullptr;

  void rotate(Node *A, Node *B) {
    Node *parent = A->parent;

    if (A->left == B) {
      A->setL(B->right);
      B->setR(A);
    } else {
      A->setR(B->left);
      B->setL(A);
    }

    if (!parent)
      root = B, B->parent = nullptr;
    else if (parent->left == A)
      parent->setL(B);
    else
      parent->setR(B);
  }

  void splay(Node *A) {
    while (A != root) {
      Node *B = A->parent;
      Node *C = A->parent->parent;

      if (B == root) {
        rotate(B, A);
        break;
      }

      if ((C->left && C->left->left == A) ||
          (C->right && C->right->right == A)) {
        rotate(C, B);
        rotate(B, A);
      } else {
        rotate(B, A);
        rotate(C, A);
      }
    }
  }

  void print(Node *curr) {
    if (!curr)
      return;
    print(curr->left);
    std::cout << curr->value << " ";
    print(curr->right);
  }

  Node *get(const T &value) {
    Node *z = root;
    while (z) {
      if (z->value < value)
        z = z->right;
      else if (value < z->value)
        z = z->left;
      else
        return z;
    }
    return nullptr;
  }

  void replace(Node *u, Node *v) {
    if (!u->parent)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    if (v)
      v->parent = u->parent;
  }

public:
  SplayTree() {}
  ~SplayTree() { delete root; }

  void insert(T value) {
    Node *B = nullptr;
    Node *A = root;

    while (A) {
      B = A;

      if (value < A->value)
        A = A->left;
      else
        A = A->right;
    }

    Node *C = new Node;
    C->value = value;

    if (root == nullptr) {
      root = C;
    } else {
      if (value < B->value)
        B->setL(C);
      else
        B->setR(C);
      splay(C);
    }
  }

  void erase(T value) {
    Node *z = get(value);
    if (!z)
      return;

    splay(z);

    if (!z->left)
      replace(z, z->right);
    else if (!z->right)
      replace(z, z->left);
    else {
      Node *y = z->right;
      while (y->left)
        y = y->left;

      if (y->parent != z) {
        replace(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      replace(z, y);
      y->left = z->left;
      y->left->parent = y;
    }
    z->left = z->right = nullptr;
    delete z;
  }

  bool find(const T &value) { return get(value) != nullptr; }

  void print() {
    print(root);
    std::cout << std::endl;
  }
};