#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "JobManager.h"
#include <string>

// A minimal, dependency-free HTTP server (raw Windows sockets) that exposes
// JobManager's data over a small JSON REST API so the HTML/CSS/JS frontend
// can talk to the existing C++ backend. It does not replace or modify the
// console application in main.cpp — it is a separate program (main_server.cpp)
// that reuses the same Job / JobManager classes.
class HttpServer
{
private:
    JobManager &jobManager;

    struct Request
    {
        std::string method;
        std::string path;
        std::string query;
        std::string body;
    };

    Request parseRequest(const std::string &raw) const;
    std::string getQueryParam(const std::string &query, const std::string &key) const;
    std::string extractJsonStringField(const std::string &body, const std::string &key) const;
    float extractJsonNumberField(const std::string &body, const std::string &key) const;

    void handleClient(unsigned long long clientSocket);
    std::string buildResponse(int statusCode, const std::string &statusText,
                               const std::string &contentType, const std::string &body) const;

public:
    explicit HttpServer(JobManager &manager);
    void start(int port);
};

#endif
