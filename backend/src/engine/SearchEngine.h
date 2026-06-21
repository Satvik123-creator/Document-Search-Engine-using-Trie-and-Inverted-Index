#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Trie.h"

using namespace std;
#include "InvertedIndex.h"
#include "Ranker.h"
#include "../parser/DocumentParser.h"
#include "../utils/Timer.h"
#include "../models/Statistics.h"
#include "../models/SearchResult.h"

/**
 * SearchEngine is the top-level coordinator that owns the
 * Trie, InvertedIndex, DocumentParser, and Ranker.
 *
 * Typical workflow:
 *   1. buildIndex(folderPath) — reads, tokenizes, and indexes all .txt files
 *   2. search(query)          — returns ranked SearchResults
 *   3. autocomplete(prefix)   — returns word completions from the Trie
 *   4. statistics()           — returns index stats (doc count, term count, etc.)
 */
class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine() = default;

    void buildIndex(const string& folderPath);

    vector<SearchResult> search(const string& query) const;

    vector<string> autocomplete(const string& prefix) const;

    Statistics statistics() const;

private:
    Trie trie;
    InvertedIndex index;
    DocumentParser parser;
    Ranker ranker;
    int documentCount;
    int totalTokenCount;
    double indexingTimeMs;
    mutable double searchTimeMs;
    mutable double autocompleteTimeMs;
    unordered_map<int, vector<string>> docTokens;
};

#endif
