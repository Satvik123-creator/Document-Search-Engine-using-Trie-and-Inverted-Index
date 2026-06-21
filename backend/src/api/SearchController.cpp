#include "SearchController.h"

using namespace std;

SearchController::SearchController(string dataDir)
    : dataDir(move(dataDir)) {}

void SearchController::buildIndex() {
    engine.buildIndex(dataDir);
}

vector<SearchResult> SearchController::handleSearch(const string& query) const {
    return engine.search(query);
}

vector<string> SearchController::handleAutocomplete(const string& prefix) const {
    return engine.autocomplete(prefix);
}

Statistics SearchController::handleStats() const {
    return engine.statistics();
}
