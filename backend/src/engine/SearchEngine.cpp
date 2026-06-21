#include "SearchEngine.h"
#include "../parser/Tokenizer.h"
#include <algorithm>
#include <set>

using namespace std;

SearchEngine::SearchEngine()
    : ranker(index, 0), documentCount(0), totalTokenCount(0),
      indexingTimeMs(0.0), searchTimeMs(0.0), autocompleteTimeMs(0.0) {}

void SearchEngine::buildIndex(const string& folderPath) {
    Timer timer;
    timer.start();

    auto documents = parser.parseDirectory(folderPath);
    documentCount = static_cast<int>(documents.size());

    for (const auto& doc : documents) {
        for (const auto& token : doc.tokens) {
            trie.insert(token);
            index.addWord(token, doc.id);
        }
        totalTokenCount += static_cast<int>(doc.tokens.size());
        docTokens[doc.id] = doc.tokens;
    }

    // Recreate ranker now that documentCount is known
    ranker = Ranker(index, documentCount);

    timer.stop();
    indexingTimeMs = timer.elapsedMilliseconds();
}

vector<SearchResult> SearchEngine::search(const string& query) const {
    Timer timer;
    timer.start();

    Tokenizer tokenizer;
    auto queryTokens = tokenizer.tokenize(query);

    if (queryTokens.empty()) {
        timer.stop();
        searchTimeMs = timer.elapsedMilliseconds();
        return {};
    }

    // Collect matching doc IDs via intersection across query terms
    auto firstResults = index.searchWord(queryTokens[0]);
    set<int> resultSet(firstResults.begin(), firstResults.end());

    for (size_t i = 1; i < queryTokens.size(); ++i) {
        auto nextResults = index.searchWord(queryTokens[i]);
        set<int> nextSet(nextResults.begin(), nextResults.end());

        set<int> intersection;
        for (int id : resultSet) {
            if (nextSet.count(id)) {
                intersection.insert(id);
            }
        }
        resultSet = move(intersection);

        if (resultSet.empty()) {
            break;
        }
    }

    vector<int> docIds(resultSet.begin(), resultSet.end());

    auto results = ranker.rank(query, docIds, docTokens);

    timer.stop();
    searchTimeMs = timer.elapsedMilliseconds();

    return results;
}

vector<string> SearchEngine::autocomplete(const string& prefix) const {
    Timer timer;
    timer.start();

    auto results = trie.autocomplete(prefix);

    timer.stop();
    autocompleteTimeMs = timer.elapsedMilliseconds();

    return results;
}

Statistics SearchEngine::statistics() const {
    Statistics stats;
    stats.totalDocuments = documentCount;
    stats.totalTerms = static_cast<int>(index.getUniqueWordCount());
    stats.averageDocumentLength = documentCount > 0
        ? static_cast<double>(totalTokenCount) / documentCount
        : 0.0;
    stats.indexSize = static_cast<double>(index.getIndexSize());
    stats.indexingTimeMs = indexingTimeMs;
    stats.searchTimeMs = searchTimeMs;
    stats.autocompleteTimeMs = autocompleteTimeMs;
    return stats;
}
