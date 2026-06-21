#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <string>

using namespace std;

struct SearchResult {
    int docId;
    double score;
    string snippet;
};

#endif
