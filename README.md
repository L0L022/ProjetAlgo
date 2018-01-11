# ProjetAlgo

Projet d’algorithmie 2017-2018 sur le codage de Huffman.

Aide :

Usage: huff [options]
This program let you compress and extract a file with the huffman algorithm based on a corpus.

Options:
  -h, --help            Displays this help.
  -v, --version         Displays version information.
  -c, --compress        Compress from input to output.
  -x, --extract         Extract from input to output.
  -i, --input <file>    Set <file> as input. Default is stdin.
  -o, --output <file>   Set <file> as output. Default is stdout.
  --as_corpus <file>    Analyse <file> and use it as a corpus.
  --load_corpus <file>  Load corpus from <file>.
  --save_corpus <file>  Save corpus to <file>.
  --save_tree <file>    Write a Graphviz dot file of the huffman tree to
                        <file>.
