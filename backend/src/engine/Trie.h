#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Represents a single node in the Trie.
 *
 * Each node holds a map of child characters and a flag
 * indicating whether a complete word ends here.
 */
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() : isEnd(false) {}
};

/**
 * A Trie (prefix tree) supporting insertion, search,
 * prefix-matching, and autocomplete.
 *
 * Time complexities:
 *   - insert:      O(L) where L is word length
 *   - search:      O(L)
 *   - startsWith:  O(L)
 *   - autocomplete: O(L + N) where N is total nodes in subtree
 */
class Trie {
public:
    Trie();
    ~Trie();

    void insert(const string& word);

    bool search(const string& word) const;

    bool startsWith(const string& prefix) const;

    vector<string> autocomplete(const string& prefix) const;

private:
    TrieNode* root;

    void clear(TrieNode* node);

    void collectWords(TrieNode* node,
                      const string& prefix,
                      vector<string>& results) const;
};

#endif
