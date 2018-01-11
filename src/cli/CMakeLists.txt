set(SRC main.cpp Graphic.cpp)

add_executable(cli ${SRC})
target_include_directories(cli SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(cli huffman)
target_link_libraries(cli Qt5::Core)

install(TARGETS cli DESTINATION bin RENAME huff)
