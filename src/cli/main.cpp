#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>

#include <cli/Graphic.hpp>
#include <huffman/CharactersFrequency.hpp>
#include <huffman/Codec.hpp>
#include <huffman/Corpus.hpp>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("huff");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::translate(
      "main",
      "This program let you compress and extract a file with the huffman "
      "algorithm based on a corpus."));
  parser.addHelpOption();
  parser.addVersionOption();

  parser.addOptions({
      {{"c", "compress"},
       QCoreApplication::translate("main", "Compress from input to output.")},
      {{"x", "extract"},
       QCoreApplication::translate("main", "Extract from input to output.")},
      {{"i", "input"},
       QCoreApplication::translate("main",
                                   "Set <file> as input. Default is stdin."),
       QCoreApplication::translate("main", "file")},
      {{"o", "output"},
       QCoreApplication::translate("main",
                                   "Set <file> as output. Default is stdout."),
       QCoreApplication::translate("main", "file")},
      {"as_corpus",
       QCoreApplication::translate("main",
                                   "Analyse <file> and use it as a corpus."),
       QCoreApplication::translate("main", "file")},
      {"load_corpus",
       QCoreApplication::translate("main", "Load corpus from <file>."),
       QCoreApplication::translate("main", "file")},
      {"save_corpus",
       QCoreApplication::translate("main", "Save corpus to <file>."),
       QCoreApplication::translate("main", "file")},
        {"save_tree",
         QCoreApplication::translate("main", "Write a Graphviz dot file of the huffman tree to <file>."),
         QCoreApplication::translate("main", "file")},
  });

  parser.process(app);

  bool compress = parser.isSet("compress");
  bool extract = parser.isSet("extract");
  bool input = parser.isSet("input");
  bool output = parser.isSet("output");
  bool as_corpus = parser.isSet("as_corpus");
  bool load_corpus = parser.isSet("load_corpus");
  bool save_corpus = parser.isSet("save_corpus");
  bool save_tree = parser.isSet("save_tree");


  if (compress and extract) {
    qCritical() << QCoreApplication::translate(
        "main", "You can't use compress and extract at the same time.");
    return -1;
  }

  if (as_corpus and load_corpus) {
    qCritical() << QCoreApplication::translate(
        "main", "You can't use as_corpus and load_corpus at the same time.");
    return -1;
  }

  std::stringstream output_buff;
  std::ostream * output_s = &std::cout;

  Huffman::Codec codec;
  codec.input = &std::cin;
  codec.output = &output_buff;

  std::ifstream input_file;
  if (input) {
    input_file.open(parser.value("input").toStdString(), std::ios::binary);

    if (!input_file.is_open()) {
      qCritical() << QCoreApplication::translate(
                         "main", "Can't open %1 file for reading.")
                         .arg(parser.value("input"));
      return -1;
    }
    codec.input = &input_file;
  }

  std::ofstream output_file;
  if (output) {
    output_file.open(parser.value("output").toStdString(),
                     std::ios::binary | std::ios::out);

    if (!output_file.is_open()) {
      qCritical() << QCoreApplication::translate(
                         "main", "Can't open %1 file for writing.")
                         .arg(parser.value("output"));
      return -1;
    }
    output_s = &output_file;
  }

  std::unique_ptr<Huffman::Corpus> corpus;

  std::ifstream corpus_file;

  if (as_corpus) {
    corpus_file.open(parser.value("as_corpus").toStdString(), std::ios::binary);
    if (!corpus_file.is_open()) {
      qCritical() << QCoreApplication::translate(
                         "main", "Can't open %1 file for reading.")
                         .arg(parser.value("as_corpus"));
      return -1;
    }
    corpus = std::make_unique<Huffman::Corpus>(corpus_file);
  }

  if (load_corpus) {
    corpus_file.open(parser.value("load_corpus").toStdString(),
                     std::ios::binary);
    if (!corpus_file.is_open()) {
      qCritical() << QCoreApplication::translate(
                         "main", "Can't open %1 file for reading.")
                         .arg(parser.value("load_corpus"));
      return -1;
    }
    corpus = std::make_unique<Huffman::Corpus>(
        Huffman::Corpus::read_save(corpus_file));
  }

  if (!corpus) {
    qCritical() << QCoreApplication::translate("main",
                                               "No corpus have been set.");
    return -1;
  }

  std::ofstream corpus_file_save;

  if (save_corpus) {
    corpus_file_save.open(parser.value("save_corpus").toStdString(),
                          std::ios::binary | std::ios::out);
    if (!corpus_file_save.is_open()) {
      qCritical() << QCoreApplication::translate(
                         "main", "Can't open %1 file for writing.")
                         .arg(parser.value("save_corpus"));
      return -1;
    }
    corpus->write_save(corpus_file_save);
  }

  if (save_tree) {
      std::ofstream file(parser.value("save_tree").toStdString(),
                         std::ios::binary | std::ios::out);
      if (!file.is_open()) {
        qCritical() << QCoreApplication::translate(
                           "main", "Can't open %1 file for writing.")
                           .arg(parser.value("save_tree"));
        return -1;
      }
      Cli::Graphic::makeDOT(corpus->tree(), file);
  }

  if (compress)
    codec.compress(corpus->charactersCode());

  if (extract)
    codec.uncompress(corpus->tree());

  *output_s << output_buff.rdbuf();

  return 0;
}
