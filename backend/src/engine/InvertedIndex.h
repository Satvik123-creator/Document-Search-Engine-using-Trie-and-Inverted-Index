#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * InvertedIndex maps each word to the set of document IDs
 * that contain it.
 *
 * Complexity:
 *   - addWord:                O(1) average
 *   - searchWord:             O(K) where K = size of the posting list
 *   - getDocumentFrequency:   O(1) average
 *   - getUniqueWordCount:     O(1)
 */
class InvertedIndex {
public:
    InvertedIndex() = default;

    void addWord(const string& word, int documentId);

    vector<int> searchWord(const string& word) const;

    int getDocumentFrequency(const string& word) const;

    size_t getUniqueWordCount() const;

    size_t getIndexSize() const;

private:
    unordered_map<string, unordered_set<int>> index;
};

#endif
