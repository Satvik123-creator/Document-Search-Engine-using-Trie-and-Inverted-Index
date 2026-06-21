#include "Tokenizer.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool Tokenizer::isPunctuation(char ch) const {
    return ispunct(static_cast<unsigned char>(ch));
}

vector<string> Tokenizer::tokenize(const string& text) const {
    vector<string> tokens;
    string current;

    for (char ch : text) {
        if (isPunctuation(ch)) {
            continue;
        }
        if (isspace(static_cast<unsigned char>(ch))) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}
