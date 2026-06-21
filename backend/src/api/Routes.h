#ifndef ROUTES_H
#define ROUTES_H

#include <string>
#include "SearchController.h"

using namespace std;

class Routes {
public:
    Routes() = delete;

    static void start(SearchController& controller, int port = 8080);

private:
    static string handleRequest(const string& method, const string& path,
                                const string& queryString, SearchController& controller);
    static string urlDecode(const string& input);
    static string jsonEscape(const string& input);
    static void sendResponse(int clientSock, int statusCode,
                             const string& statusText, const string& body);
};

#endif
