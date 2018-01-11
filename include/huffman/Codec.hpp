#ifndef HUFFMAN_CODEC_HPP
#define HUFFMAN_CODEC_HPP

#include <iostream>

#include "CharactersCode.hpp"
#include "Tree.hpp"

namespace Huffman {
class Codec {
public:
  Codec();

  void compress(const CharactersCode &cc);
  void uncompress(const Tree &t);

  std::istream *input;
  std::ostream *output;
};
} // namespace Huffman

#endif
