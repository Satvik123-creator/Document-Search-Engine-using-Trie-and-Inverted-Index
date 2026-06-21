#ifndef RANKER_H
#define RANKER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../models/SearchResult.h"

using namespace std;

class InvertedIndex;

/**
 * Ranker computes TF-IDF scores for documents matching a query.
 *
 * TF  = (count of term in document) / (total terms in document)
 * IDF = log(totalDocuments / documentFrequency(term))
 * Score = sum of (TF * IDF) over all query terms
 *
 * Results are sorted by score descending.
 */
class Ranker {
public:
    Ranker(const InvertedIndex& index, int totalDocuments);

    vector<SearchResult> rank(
        const string& query,
        const vector<int>& docIds,
        const unordered_map<int, vector<string>>& docTokens) const;

private:
    const InvertedIndex* index;
    int totalDocuments;

    double computeTF(const vector<string>& tokens,
                     const string& term) const;

    double computeIDF(const string& term) const;
};

#endif
