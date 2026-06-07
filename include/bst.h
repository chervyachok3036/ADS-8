// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int frequency;
        Node* left;
        Node* right;

        Node(T val) : value(val), frequency(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertHelper(Node* node, T value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->value) {
            node->right = insertHelper(node->right, value);
        } else {
            node->frequency++;
        }

        return node;
    }

    Node* searchHelper(Node* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            return searchHelper(node->left, value);
        } else if (value > node->value) {
            return searchHelper(node->right, value);
        } else {
            return node;
        }
    }

    int depthHelper(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftDepth = depthHelper(node->left);
        int rightDepth = depthHelper(node->right);

        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    void deleteHelper(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteHelper(node->left);
        deleteHelper(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        deleteHelper(root);
    }

    void insert(T value) {
        root = insertHelper(root, value);
    }

    bool search(T value) {
        return searchHelper(root, value) != nullptr;
    }

    int getFrequency(T value) {
        Node* node = searchHelper(root, value);
        if (node != nullptr) {
            return node->frequency;
        }
        return 0;
    }

    int depth() {
        return depthHelper(root);
    }

    void inorder() {
        inorderHelper(root);
    }

    void inorderHelper(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorderHelper(node->left);
        std::cout << node->value << " (" << node->frequency << ") ";
        inorderHelper(node->right);
    }

    Node* getRoot() const {
        return root;
    }

    struct Node* getRootNode() {
        return root;
    }

    friend class FreqAnalyzer;
};

#endif  // INCLUDE_BST_H_
