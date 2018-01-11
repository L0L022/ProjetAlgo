#include <huffman/Corpus.hpp>

using namespace Huffman;

Corpus::Corpus(CharactersFrequency &&cf)
    : _cf(std::move(cf)), _t(_cf), _cc(make_CharactersCode(_t)) {}

Corpus::Corpus(std::istream &is) : Corpus(count_occurrences(is)) {}

Corpus Corpus::read_save(std::istream &is) {
  CharactersFrequency cf;
  char c;
  size_t f;
  while (is.good()) {
    is.read(reinterpret_cast<char *>(&c), sizeof(c));
    is.read(reinterpret_cast<char *>(&f), sizeof(f));
    cf[c] = f;
  }
  return Corpus(std::move(cf));
}

void Corpus::write_save(std::ostream &os) {
  for (const auto &p : _cf) {
    os.write(reinterpret_cast<const char *>(&p.first), sizeof(char));
    os.write(reinterpret_cast<const char *>(&p.second), sizeof(size_t));
  }
}
