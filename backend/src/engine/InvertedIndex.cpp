#include "InvertedIndex.h"
using namespace std;

void InvertedIndex::addWord(const string& word, int documentId) {
    index[word].insert(documentId);
}

vector<int> InvertedIndex::searchWord(const string& word) const {
    auto it = index.find(word);
    if (it == index.end()) {
        return {};
    }
    return vector<int>(it->second.begin(), it->second.end());
}

int InvertedIndex::getDocumentFrequency(const string& word) const {
    auto it = index.find(word);
    if (it == index.end()) {
        return 0;
    }
    return static_cast<int>(it->second.size());
}

size_t InvertedIndex::getUniqueWordCount() const {
    return index.size();
}

size_t InvertedIndex::getIndexSize() const {
    size_t total = 0;
    for (const auto& pair : index) {
        total += pair.second.size();
    }
    return total;
}
