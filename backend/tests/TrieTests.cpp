#include "../src/engine/Trie.h"
#include <cassert>

void testInsertAndSearch() {
    Trie trie;
    trie.insert("hello");
    assert(trie.search("hello") == true);
    assert(trie.search("world") == false);
}

void testAutocomplete() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    auto results = trie.autocomplete("app");
    assert(results.size() == 3);
}

int main() {
    testInsertAndSearch();
    testAutocomplete();
    return 0;
}
