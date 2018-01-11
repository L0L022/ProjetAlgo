#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <memory>

namespace Huffman {
class Node {
public:
  typedef std::unique_ptr<Node> Ptr;

  Node(const char character, const size_t frequency);
  Node(Ptr &&left, Ptr &&right);

  char character() const { return _character; }
  size_t frequency() const { return _frequency; }

  Node &left() const { return *_left; }
  Node &right() const { return *_right; }

  bool isLeaf() const { return _left == nullptr and _right == nullptr; }
  bool isBranch() const { return _left != nullptr and _right != nullptr; }

  bool operator<(const Node &n) { return _frequency < n._frequency; }
  bool operator>(const Node &n) { return _frequency > n._frequency; }

private:
  const Ptr _left, _right;
  const char _character;
  const size_t _frequency;
};
} // namespace Huffman

#endif
