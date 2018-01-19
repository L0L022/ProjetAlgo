#include <cli/Graphic.hpp>

using namespace Cli;

void Graphic::makeDOT(const Huffman::Tree &t, std::ostream &os) {
  os << "digraph HuffmanTree {\nnode [shape = record,height=.1];\n";
  dotPrint(t.root(), os);
  os << "\n}\n";
}

void Graphic::dotPrint(const Huffman::Node &n, std::ostream &os) {
  os << '"' << reinterpret_cast<size_t>(&n) << "\" [";
  if (n.isLeaf())
    os << "fontcolor=red,";
  os << "label=\"<f0> |<f1> ";
  if (n.isLeaf()) {
    os << "\\\"";
    switch (n.character()) {
    case '"':
    case '\\':
    case '<':
    case '>':
    case '{':
    case '}':
    case '|':
      os << '\\';
      break;
    }
    os << n.character() << "\\\" : ";
  }
  os << n.frequency() << "|<f2> \"];\n";

  if (n.isBranch()) {
    os << '"' << reinterpret_cast<size_t>(&n) << "\":f0 -> \""
       << reinterpret_cast<size_t>(&n.left()) << "\":f1 [label=\"0\"];\n";
    os << '"' << reinterpret_cast<size_t>(&n) << "\":f2 -> \""
       << reinterpret_cast<size_t>(&n.right()) << "\":f1 [label=\"1\"];\n";
    dotPrint(n.left(), os);
    dotPrint(n.right(), os);
  }
}
