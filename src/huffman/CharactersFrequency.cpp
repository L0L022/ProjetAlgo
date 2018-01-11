#include <huffman/CharactersFrequency.hpp>

using namespace Huffman;

CharactersFrequency Huffman::count_occurrences(std::istream &is) {
  CharactersFrequency cf;
  for (char c = is.get(); is.good(); c = is.get()) {
    try {
      ++cf.at(c);
    } catch (const std::out_of_range &e) {
      cf[c] = 1;
    }
  }
  return cf;
}
