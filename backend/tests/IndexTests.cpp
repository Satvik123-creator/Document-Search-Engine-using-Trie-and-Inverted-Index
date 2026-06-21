#include "../src/engine/InvertedIndex.h"
#include <cassert>

void testAddAndGet() {
    InvertedIndex index;
    index.addDocument("hello", 1);
    index.addDocument("hello", 2);
    auto list = index.getPostingList("hello");
    assert(list.size() == 2);
    assert(list[0] == 1);
    assert(list[1] == 2);
}

int main() {
    testAddAndGet();
    return 0;
}
