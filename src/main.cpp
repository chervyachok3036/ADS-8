// Copyright 2021 NNTU-CS
#include "bst.h"

#include <iostream>
#include <string>

void MakeTree(BST<std::string>& tree, const char* filename);
void PrintFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;

  MakeTree(tree, "src/war_peace.txt");

  std::cout << "Tree depth:   " << tree.Depth() << "\n";
  std::cout << "Unique words: " << tree.Size()  << "\n";

  std::cout << "\nFrequency of 'war':   " << tree.Search("war")   << "\n";
  std::cout << "Frequency of 'peace': " << tree.Search("peace") << "\n";
  std::cout << "Frequency of 'the':   " << tree.Search("the")   << "\n";

  std::cout << "\nWords sorted by frequency:\n";
  PrintFreq(tree);

  return 0;
}
