#include <huffman/CharactersCode.hpp>

// #include <pa ir>

using namespace Huffman;

CharactersCode Huffman::make_CharactersCode(const Tree &t) {
  CharactersCode cc;
  std::vector<std::pair<Node *, std::vector<bool>>> nodes{{&t.root(), {}}};
  while (!nodes.empty()) {
    std::vector<std::pair<Node *, std::vector<bool>>> n;
    for (auto &p : nodes) {
      if (p.first->isLeaf()) {
        cc[p.first->character()] = std::move(p.second);
      } else {
        n.push_back({&p.first->left(), p.second});
        n.back().second.push_back(false);
        n.push_back({&p.first->right(), p.second});
        n.back().second.push_back(true);
      }
    }
    nodes = std::move(n);
  }
  return cc;
}
