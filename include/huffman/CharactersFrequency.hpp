#ifndef HUFFMAN_CHARACTERSFREQUENCY_HPP
#define HUFFMAN_CHARACTERSFREQUENCY_HPP

#include <iostream>
#include <map>

namespace Huffman {
typedef std::map<char, size_t> CharactersFrequency;

CharactersFrequency count_occurrences(std::istream &is);
} // namespace Huffman

#endif
