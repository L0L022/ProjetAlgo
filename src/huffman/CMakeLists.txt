set(SRC CharactersCode.cpp CharactersFrequency.cpp Codec.cpp Corpus.cpp Node.cpp Tree.cpp)
add_library(huffman STATIC ${SRC})
target_include_directories(huffman SYSTEM PUBLIC ${INCLUDE_DIR})
