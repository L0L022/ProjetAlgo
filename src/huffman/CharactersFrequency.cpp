#include <huffman/CharactersFrequency.hpp>

#include <limits>

using namespace Huffman;

CharactersFrequency Huffman::count_occurrences(std::istream &is) {
  CharactersFrequency cf;
  for (char c = std::numeric_limits<char>::min();
       c < std::numeric_limits<char>::max(); ++c)
    cf[c] = 0;
  cf.erase('\0');
  for (char c = is.get(); is.good(); c = is.get())
    ++cf.at(c);
  return cf;
}
