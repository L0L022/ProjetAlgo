#ifndef CLI_GRAPHIC_HPP
#define CLI_GRAPHIC_HPP

#include <iostream>

#include <huffman/Tree.hpp>

namespace Cli {
class Graphic {
public:
 static void makeDOT(const Huffman::Tree &t, std::ostream &os);

private:
 static void dotPrint(const Huffman::Node &n, std::ostream &os);
};
} // namespace Cli

#endif

