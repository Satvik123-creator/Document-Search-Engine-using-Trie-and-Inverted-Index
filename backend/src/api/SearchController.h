#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include <string>
#include <vector>
#include "../engine/SearchEngine.h"

using namespace std;
#include "../models/SearchResult.h"
#include "../models/Statistics.h"

class SearchController {
public:
    explicit SearchController(string dataDir);

    void buildIndex();

    vector<SearchResult> handleSearch(const string& query) const;

    vector<string> handleAutocomplete(const string& prefix) const;

    Statistics handleStats() const;

private:
    SearchEngine engine;
    string dataDir;
};

#endif
