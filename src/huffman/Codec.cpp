#include <huffman/Codec.hpp>

#include <bitset>
#include <iostream>
#include <string>

using namespace Huffman;

Codec::Codec() : input(nullptr), output(nullptr) {}

void Codec::compress(const CharactersCode &cc) {
  // check streams
  size_t begin = output->tellp();
  std::bitset<8> bits(0b00000000);
  output->put(bits.to_ulong());
  size_t i = 0;
  for (char c = input->get(); input->good() && output->good();
       c = input->get()) {
    for (bool b : cc.at(c)) {
      bits[bits.size() - 1 - i] = b;
      if (i == bits.size() - 1) {
        output->put(bits.to_ulong());
        bits.reset();
        i = 0;
      } else {
        ++i;
      }
    }
  }

  if (i > 0) {
    output->put(bits.to_ulong());
    output->seekp(begin);
    bits.reset();
    for (size_t j = 0; j < i; ++j)
      bits[bits.size() - 1 - j] = true;
    output->put(bits.to_ulong());
    output->seekp(0, std::ios_base::end);
  }

  // check if streams are still ok
}

void Codec::uncompress(const Tree &t) {
  // check streams
  std::bitset<8> ignore_bits = input->get();
  Tree::Iterator it(t.root());
  std::bitset<8> bits = input->get();
  char next_c = input->get();
  bool is_eof = input->eof();
  size_t bits_size = bits.size();
  while (!is_eof) {
    is_eof = input->eof();

    if (is_eof and ignore_bits.any()) {
      bits &= ignore_bits;
      bits_size = ignore_bits.count();
    }

    for (size_t i = 0; i < bits_size; ++i) {
      it += bits[bits.size() - 1 - i];
      if (it->isLeaf()) {
        output->put(it->character());
        it = t.root();
      }
    }

    bits = next_c;
    next_c = input->get();
  }

  // check if streams are still ok
}
