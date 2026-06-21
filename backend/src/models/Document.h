#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

using namespace std;

struct Document {
    int id;
    string content;
    string path;
    vector<string> tokens;
};

#endif
