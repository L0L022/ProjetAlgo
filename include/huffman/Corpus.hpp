#ifndef HUFFMAN_CORPUS_HPP
#define HUFFMAN_CORPUS_HPP

#include <iostream>

#include "CharactersCode.hpp"
#include "CharactersFrequency.hpp"
#include "Tree.hpp"

namespace Huffman {
class Corpus {
public:
  Corpus(CharactersFrequency &&cf);
  Corpus(std::istream &is);

  const Tree &tree() const { return _t; }
  const CharactersCode &charactersCode() const { return _cc; }

  static Corpus read_save(std::istream &is);
  void write_save(std::ostream &os);

private:
  CharactersFrequency _cf;
  Tree _t;
  CharactersCode _cc;
};
} // namespace Huffman

#endif
