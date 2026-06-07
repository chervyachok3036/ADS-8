// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 public:
  void insert(const T& value) { root_ = Insert(std::move(root_), value); }

  int depth() const { return Depth(root_.get()); }

  int search(const T& value) const {
    Node* node = Search(root_.get(), value);
    return node ? node->count : 0;
  }

  int size() const { return Size(root_.get()); }

  void collectInfo(std::vector<std::pair<T, int>>& items) const {
    Collect(root_.get(), items);
  }

 private:
  struct Node {
    T value;
    int count;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const T& val) : value(val), count(1) {}
  };

  std::unique_ptr<Node> root_;

  std::unique_ptr<Node> Insert(std::unique_ptr<Node> node, const T& value) {
    if (!node) return std::make_unique<Node>(value);
    if (value < node->value) {
      node->left = Insert(std::move(node->left), value);
    } else if (value > node->value) {
      node->right = Insert(std::move(node->right), value);
    } else {
      ++node->count;
    }
    return node;
  }

  int Depth(const Node* node) const {
    if (!node) return -1;
    return 1 + std::max(Depth(node->left.get()), Depth(node->right.get()));
  }

  Node* Search(Node* node, const T& value) const {
    if (!node) return nullptr;
    if (value == node->value) return node;
    if (value < node->value) return Search(node->left.get(), value);
    return Search(node->right.get(), value);
  }

  int Size(const Node* node) const {
    if (!node) return -1;
    return 1 + Size(node->left.get()) + Size(node->right.get());
  }

  void Collect(const Node* node, std::vector<std::pair<T, int>>& items) const {
    if (!node) return;
    Collect(node->left.get(), items);
    items.push_back({node->value, node->count});
    Collect(node->right.get(), items);
  }
};

#endif  // INCLUDE_BST_H_
