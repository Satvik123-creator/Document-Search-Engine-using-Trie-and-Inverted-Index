#include "DocumentParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>

using namespace std;

DocumentParser::DocumentParser() : nextId(0) {}

Document DocumentParser::parseFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filePath);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    Document doc;
    doc.id = nextId++;
    doc.content = content;
    doc.path = filePath;
    doc.tokens = tokenizer.tokenize(content);

    return doc;
}

vector<Document> DocumentParser::parseDirectory(const string& directoryPath) {
    vector<Document> docs;

    // Check if directory exists using GetFileAttributes
    DWORD attrs = GetFileAttributesA(directoryPath.c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES || !(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
        throw runtime_error("Directory does not exist: " + directoryPath);
    }

    string pattern = directoryPath + "\\*.txt";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(pattern.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return docs;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }
        string fullPath = directoryPath + "\\" + findData.cFileName;
        try {
            docs.push_back(parseFile(fullPath));
        } catch (const exception& e) {
            cerr << "Skipping " << fullPath << ": " << e.what() << endl;
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return docs;
}
