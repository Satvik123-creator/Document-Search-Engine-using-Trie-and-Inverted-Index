cmake_minimum_required(VERSION 3.14)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine
    src/main.cpp
    src/engine/SearchEngine.cpp
    src/engine/InvertedIndex.cpp
    src/engine/Trie.cpp
    src/engine/Ranker.cpp
    src/parser/DocumentParser.cpp
    src/parser/Tokenizer.cpp
    src/api/SearchController.cpp
    src/api/Routes.cpp
    src/utils/Timer.cpp
)

target_link_libraries(search_engine PRIVATE ws2_32 winmm)
