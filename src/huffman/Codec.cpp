#include <huffman/Codec.hpp>

#include <bitset>

using namespace Huffman;

Codec::Codec() : input(nullptr), output(nullptr) {}

void Codec::compress(const CharactersCode &cc) {
  // check streams

  std::bitset<8> bits;
  size_t i = 0;
  for (char c = input->get(); input->good() && output->good();
       c = input->get()) {
    for (bool b : cc.at(c)) {
        bits[i] = b;
      if (i == bits.size() - 1) {
        output->put(bits.to_ulong());
        i = 0;
      } else {
        ++i;
      }
    }
  }
  if (i > 0)
    output->put(bits.to_ulong());

  // check if streams are still ok
}

void Codec::uncompress(const Tree &t) {
  // check streams

  Tree::Iterator it(t.root());
  for (std::bitset<8> bits = input->get(); input->good() and output->good();
       bits = input->get()) {
    for (size_t i = 0; i < bits.size(); ++i) {
      it += bits[i];
      if (it->isLeaf()) {
        output->put(it->character());
        it = t.root();
      }
    }
  }

  // check if streams are still ok
}
