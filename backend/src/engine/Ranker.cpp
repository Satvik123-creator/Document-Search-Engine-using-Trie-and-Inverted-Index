#include "Ranker.h"
#include "InvertedIndex.h"
#include "../parser/Tokenizer.h"
#include <algorithm>
#include <cmath>
#include <unordered_set>

using namespace std;

Ranker::Ranker(const InvertedIndex& index, int totalDocuments)
    : index(&index), totalDocuments(totalDocuments) {}

double Ranker::computeTF(const vector<string>& tokens,
                         const string& term) const {
    if (tokens.empty()) {
        return 0.0;
    }
    int cnt = static_cast<int>(count(tokens.begin(), tokens.end(), term));
    return static_cast<double>(cnt) / tokens.size();
}

double Ranker::computeIDF(const string& term) const {
    int df = index->getDocumentFrequency(term);
    if (df == 0) {
        return 0.0;
    }
    return log(static_cast<double>(totalDocuments) / df);
}

vector<SearchResult> Ranker::rank(
    const string& query,
    const vector<int>& docIds,
    const unordered_map<int, vector<string>>& docTokens) const {

    Tokenizer tokenizer;
    auto queryTokens = tokenizer.tokenize(query);

    if (queryTokens.empty()) {
        return {};
    }

    // Remove duplicate query tokens so each term is scored once
    unordered_set<string> uniqueTerms(queryTokens.begin(), queryTokens.end());

    vector<SearchResult> results;
    results.reserve(docIds.size());

    for (int docId : docIds) {
        auto it = docTokens.find(docId);
        if (it == docTokens.end()) {
            continue;
        }

        const auto& tokens = it->second;
        double score = 0.0;

        for (const auto& term : uniqueTerms) {
            double tf = computeTF(tokens, term);
            if (tf == 0.0) {
                continue;
            }
            double idf = computeIDF(term);
            score += tf * idf;
        }

        results.push_back({docId, score, ""});
    }

    // Sort by score descending
    sort(results.begin(), results.end(),
              [](const SearchResult& a, const SearchResult& b) {
                  return a.score > b.score;
              });

    return results;
}
