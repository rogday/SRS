#include <Treap.h>

std::random_device Treap::Node::rd;
std::default_random_engine Treap::Node::engine(rd());
std::uniform_int_distribution<std::uint64_t>
    Treap::Node::rand(0, std::numeric_limits<std::uint64_t>::max());

std::pair<Treap::Node *, Treap::Node *> Treap::split(Treap::Node *ptr,
                                                     std::uint64_t val) {
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

Treap::Node *Treap::merge(Treap::Node *t1, Treap::Node *t2) {
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

void Treap::insert(std::uint64_t val) {
  Treap::Node *newNode = new Treap::Node(val);
  auto t = split(root, val);
  t.first = merge(t.first, newNode);
  root = merge(t.first, t.second);
}

void Treap::remove(Treap::Node *&ptr, std::uint64_t val) {
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

void Treap::print(Treap::Node *ptr) {
  if (!ptr)
    return;

  print(ptr->left);
  std::cout << (ptr->val) << " ";
  print(ptr->right);
}