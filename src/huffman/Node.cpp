#include <huffman/Node.hpp>

using namespace Huffman;

Node::Node(const char character, const size_t frequency)
    : _character(character), _frequency(frequency) {}

Node::Node(Ptr &&left, Ptr &&right)
    : _left(std::move(left)), _right(std::move(right)), _character('\0'),
      _frequency(_left->_frequency + _right->_frequency) {}
