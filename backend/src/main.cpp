#include <iostream>
#include <string>
#include "api/SearchController.h"
#include "api/Routes.h"

using namespace std;

int main(int argc, char* argv[]) {
    string dataDir = "../data/documents";
    if (argc > 1) {
        dataDir = argv[1];
    }

    SearchController controller(dataDir);

    cout << "Building index from: " << dataDir << endl;
    try {
        controller.buildIndex();
        auto stats = controller.handleStats();
        cout << "Index built: "
                  << stats.totalDocuments << " documents, "
                  << stats.totalTerms << " unique terms" << endl;
    } catch (const exception& e) {
        cerr << "Failed to build index: " << e.what() << endl;
        return 1;
    }

    Routes::start(controller, 8080);

    return 0;
}
