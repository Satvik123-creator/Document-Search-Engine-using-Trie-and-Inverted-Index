#include "Trie.h"

using namespace std;

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

/**
 * Recursively deletes all nodes in the trie to prevent memory leaks.
 */
void Trie::clear(TrieNode* node) {
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    delete node;
}

void Trie::insert(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }
    node->isEnd = true;
}

bool Trie::search(const string& word) const {
    TrieNode* node = root;
    for (char ch : word) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return false;
        }
        node = it->second;
    }
    return node->isEnd;
}

bool Trie::startsWith(const string& prefix) const {
    TrieNode* node = root;
    for (char ch : prefix) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return false;
        }
        node = it->second;
    }
    return true;
}

vector<string> Trie::autocomplete(const string& prefix) const {
    TrieNode* node = root;
    for (char ch : prefix) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return {};
        }
        node = it->second;
    }
    vector<string> results;
    collectWords(node, prefix, results);
    return results;
}

void Trie::collectWords(TrieNode* node,
                         const string& prefix,
                         vector<string>& results) const {
    if (node->isEnd) {
        results.push_back(prefix);
    }
    for (const auto& pair : node->children) {
        collectWords(pair.second, prefix + pair.first, results);
    }
}
