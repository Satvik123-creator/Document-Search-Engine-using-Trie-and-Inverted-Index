#ifndef STATISTICS_H
#define STATISTICS_H

struct Statistics {
    int totalDocuments;
    int totalTerms;
    double averageDocumentLength;
    double indexSize;
    double indexingTimeMs;
    double searchTimeMs;
    double autocompleteTimeMs;
};

#endif
