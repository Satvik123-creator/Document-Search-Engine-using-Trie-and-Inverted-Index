#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

using namespace std;

/**
 * Tokenizer converts raw text into a list of cleaned tokens.
 *
 * Processing steps:
 *   1. Convert to lowercase
 *   2. Remove punctuation
 *   3. Split on whitespace
 *
 * Complexity: O(N) where N = length of input text
 */
class Tokenizer {
public:
    Tokenizer() = default;

    vector<string> tokenize(const string& text) const;

private:
    bool isPunctuation(char ch) const;
};

#endif
