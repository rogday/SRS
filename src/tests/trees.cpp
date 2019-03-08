#include <iostream>

#include <Treap.h>

int main() {
  Treap tree;
  for (int i = 100; i >= 0; --i)
    tree.insert(i);
  tree.print();

  for (int i = 20; i < 50; ++i)
    tree.remove(i);
  tree.print();

  for (int i = 0; i < 20; ++i)
    tree.remove(i);
  for (int i = 50; i <= 100; ++i)
    tree.remove(i);
  tree.print();
}