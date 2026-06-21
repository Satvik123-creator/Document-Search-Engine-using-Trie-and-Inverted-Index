#include "Routes.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <winsock2.h>
#include <windows.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

void Routes::start(SearchController& controller, int port) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed: " << result << endl;
        return;
    }

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET) {
        cerr << "socket failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listenSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        cerr << "bind failed on port " << port << ": " << WSAGetLastError() << endl;
        closesocket(listenSock);
        WSACleanup();
        return;
    }

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "listen failed: " << WSAGetLastError() << endl;
        closesocket(listenSock);
        WSACleanup();
        return;
    }

    cout << "Search engine running on http://localhost:" << port << endl;

    while (true) {
        SOCKET clientSock = accept(listenSock, nullptr, nullptr);
        if (clientSock == INVALID_SOCKET) {
            cerr << "accept failed: " << WSAGetLastError() << endl;
            continue;
        }

        char buf[8192];
        int bytesRead = recv(clientSock, buf, sizeof(buf) - 1, 0);
        if (bytesRead > 0) {
            buf[bytesRead] = 0;

            string raw(buf);
            istringstream stream(raw);
            string method, path, httpVer;
            stream >> method >> path >> httpVer;

            size_t qPos = path.find('?');
            string queryString;
            string route = path;
            if (qPos != string::npos) {
                route = path.substr(0, qPos);
                queryString = path.substr(qPos + 1);
            }

            if (method == "GET") {
                string body = handleRequest(method, route, queryString, controller);
                sendResponse(clientSock, 200, "OK", body);
            } else {
                sendResponse(clientSock, 405, "Method Not Allowed", "{\"error\":\"Method not allowed\"}");
            }
        }

        closesocket(clientSock);
        Sleep(1);
    }

    closesocket(listenSock);
    WSACleanup();
}

string Routes::handleRequest(const string& method, const string& path,
                             const string& queryString, SearchController& controller) {
    string q;
    size_t qStart = string::npos;

    auto parseParam = [&](const string& name) -> string {
        string key = name + "=";
        size_t pos = queryString.find(key);
        if (pos == string::npos) return "";
        size_t valStart = pos + key.length();
        size_t valEnd = queryString.find('&', valStart);
        return urlDecode(queryString.substr(valStart, valEnd - valStart));
    };

    if (path == "/search") {
        q = parseParam("q");
        if (q.empty()) {
            return "{\"error\":\"Missing query parameter 'q'\"}";
        }
        auto results = controller.handleSearch(q);
        ostringstream json;
        json << "{\"query\":" << jsonEscape(q) << ",\"results\":[";
        for (size_t i = 0; i < results.size(); i++) {
            if (i > 0) json << ",";
            json << "{\"docId\":" << results[i].docId
                 << ",\"score\":" << results[i].score << "}";
        }
        json << "]}";
        return json.str();
    }

    if (path == "/autocomplete") {
        string prefix = parseParam("prefix");
        if (prefix.empty()) {
            return "{\"error\":\"Missing query parameter 'prefix'\"}";
        }
        auto suggestions = controller.handleAutocomplete(prefix);
        ostringstream json;
        json << "{\"prefix\":" << jsonEscape(prefix) << ",\"suggestions\":[";
        for (size_t i = 0; i < suggestions.size(); i++) {
            if (i > 0) json << ",";
            json << jsonEscape(suggestions[i]);
        }
        json << "]}";
        return json.str();
    }

    if (path == "/stats") {
        auto stats = controller.handleStats();
        ostringstream json;
        json << "{"
             << "\"totalDocuments\":" << stats.totalDocuments << ","
             << "\"uniqueWords\":" << stats.totalTerms << ","
             << "\"averageDocumentLength\":" << stats.averageDocumentLength << ","
             << "\"indexSize\":" << stats.indexSize << ","
             << "\"indexingTimeMs\":" << stats.indexingTimeMs << ","
             << "\"searchTimeMs\":" << stats.searchTimeMs << ","
             << "\"autocompleteTimeMs\":" << stats.autocompleteTimeMs
             << "}";
        return json.str();
    }

    return "{\"error\":\"Not found\"}";
}

string Routes::urlDecode(const string& input) {
    string result;
    result.reserve(input.length());
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '%' && i + 2 < input.length()) {
            int hi = input[i + 1];
            int lo = input[i + 2];
            hi = (hi >= 'a') ? (hi - 'a' + 10) : (hi >= 'A' ? (hi - 'A' + 10) : (hi - '0'));
            lo = (lo >= 'a') ? (lo - 'a' + 10) : (lo >= 'A' ? (lo - 'A' + 10) : (lo - '0'));
            result += (char)((hi << 4) | lo);
            i += 2;
        } else if (input[i] == '+') {
            result += ' ';
        } else {
            result += input[i];
        }
    }
    return result;
}

string Routes::jsonEscape(const string& input) {
    ostringstream out;
    out << "\"";
    for (char c : input) {
        switch (c) {
            case '"': out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default: out << c;
        }
    }
    out << "\"";
    return out.str();
}

void Routes::sendResponse(int clientSock, int statusCode,
                          const string& statusText, const string& body) {
    ostringstream header;
    header << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n"
           << "Content-Type: application/json\r\n"
           << "Access-Control-Allow-Origin: *\r\n"
           << "Content-Length: " << body.length() << "\r\n"
           << "Connection: close\r\n"
           << "\r\n";

    string response = header.str() + body;
    send(clientSock, response.c_str(), response.length(), 0);
}
