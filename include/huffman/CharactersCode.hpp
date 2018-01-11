#ifndef HUFFMAN_CHARACTERSCODE_HPP
#define HUFFMAN_CHARACTERSCODE_HPP

#include <map>
#include <vector>

#include "Tree.hpp"

namespace Huffman {
typedef std::map<char, std::vector<bool>> CharactersCode;

CharactersCode make_CharactersCode(const Tree &t);
} // namespace Huffman

#endif
