#include <huffman/Tree.hpp>

using namespace Huffman;

#include <algorithm>
#include <deque>

Tree::Tree(const CharactersFrequency &cf) {
  std::deque<Node::Ptr> nodes;
  for (const auto &p : cf)
    nodes.push_back(std::make_unique<Node>(p.first, p.second));
  while (nodes.size() > 1) {
    std::sort(nodes.begin(), nodes.end(),
              [](const Node::Ptr &l, const Node::Ptr &r) { return *l < *r; });
    auto first = std::move(*nodes.begin());
    auto second = std::move(*(nodes.begin() + 1));

    nodes.erase(nodes.begin(), nodes.begin() + 2);
    nodes.push_front(
        std::make_unique<Node>(std::move(first), std::move(second)));
  }
  _root = std::move(*nodes.begin());
}

Tree::Iterator::Iterator(Node &n) : _node(&n) {}

Tree::Iterator Tree::Iterator::operator+(const bool b) {
  if (b)
    return Iterator(_node->right());
  else
    return Iterator(_node->left());
}

Tree::Iterator &Tree::Iterator::operator+=(const bool b) {
  if (b)
    _node = &_node->right();
  else
    _node = &_node->left();

  return *this;
}
