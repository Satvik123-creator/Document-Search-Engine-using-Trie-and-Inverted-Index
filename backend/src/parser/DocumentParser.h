#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include "../models/Document.h"
#include "Tokenizer.h"

using namespace std;

/**
 * DocumentParser reads .txt files from disk, assigns sequential
 * document IDs, and produces Document objects with tokenized content.
 *
 * Designed for batch indexing of thousands of files via parseDirectory().
 *
 * Complexity: O(F * (S + T)) where:
 *   F = number of files
 *   S = total size (bytes) of each file
 *   T = token count per file
 */
class DocumentParser {
public:
    DocumentParser();

    Document parseFile(const string& filePath);

    vector<Document> parseDirectory(const string& directoryPath);

private:
    int nextId;
    Tokenizer tokenizer;
};

#endif
