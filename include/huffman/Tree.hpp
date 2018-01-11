#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include "CharactersFrequency.hpp"
#include "Node.hpp"

namespace Huffman {
class Tree {
public:
  Tree(const CharactersFrequency &cf);

  inline Node &root() const { return *_root; };

  class Iterator {
  public:
    Iterator(Node &n);

    Iterator operator=(Node &n) { _node = &n; }
    Iterator operator+(const bool b);
    Iterator &operator+=(const bool b);

    inline Node &operator*() const { return *_node; }
    inline Node *operator->() const { return _node; }

  private:
    Node *_node;
  };

private:
  Node::Ptr _root;
};
} // namespace Huffman

#endif
