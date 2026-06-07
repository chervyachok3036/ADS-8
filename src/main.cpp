// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;

  makeTree(tree, "src/war_peace.txt");

  std::cout << "Tree depth:   " << tree.depth() << "\n";
  std::cout << "Unique words: " << tree.size()  << "\n";

  std::cout << "\nFrequency of 'war':   " << tree.search("war")   << "\n";
  std::cout << "Frequency of 'peace': " << tree.search("peace") << "\n";
  std::cout << "Frequency of 'the':   " << tree.search("the")   << "\n";

  std::cout << "\nWords sorted by frequency:\n";
  printFreq(tree);

  return 0;
}
