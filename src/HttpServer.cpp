#include "../include/HttpServer.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

using namespace std;

HttpServer::HttpServer(JobManager &manager) : jobManager(manager) {}

// ---------------- Small parsing helpers ----------------
// These are deliberately simple/hand-rolled (not a general-purpose HTTP or
// JSON library) since this project has no package manager set up. They only
// need to handle the flat, known-shape requests this frontend sends.

HttpServer::Request HttpServer::parseRequest(const string &raw) const
{
    Request req;

    size_t lineEnd = raw.find("\r\n");
    string requestLine = (lineEnd == string::npos) ? raw : raw.substr(0, lineEnd);

    istringstream lineStream(requestLine);
    string fullPath;
    lineStream >> req.method >> fullPath;

    size_t qPos = fullPath.find('?');
    if (qPos != string::npos)
    {
        req.path = fullPath.substr(0, qPos);
        req.query = fullPath.substr(qPos + 1);
    }
    else
    {
        req.path = fullPath;
        req.query = "";
    }

    size_t headerEnd = raw.find("\r\n\r\n");
    if (headerEnd != string::npos)
    {
        req.body = raw.substr(headerEnd + 4);
    }

    return req;
}

string HttpServer::getQueryParam(const string &query, const string &key) const
{
    size_t pos = 0;
    while (pos < query.size())
    {
        size_t amp = query.find('&', pos);
        string pair = (amp == string::npos) ? query.substr(pos) : query.substr(pos, amp - pos);

        size_t eq = pair.find('=');
        if (eq != string::npos)
        {
            string k = pair.substr(0, eq);
            string v = pair.substr(eq + 1);
            if (k == key) return v;
        }

        if (amp == string::npos) break;
        pos = amp + 1;
    }
    return "";
}

string HttpServer::extractJsonStringField(const string &body, const string &key) const
{
    string pattern = "\"" + key + "\"";
    size_t pos = body.find(pattern);
    if (pos == string::npos) return "";

    pos = body.find(':', pos);
    if (pos == string::npos) return "";
    pos++;

    while (pos < body.size() && isspace(static_cast<unsigned char>(body[pos]))) pos++;
    if (pos >= body.size() || body[pos] != '"') return "";
    pos++;

    string result;
    while (pos < body.size() && body[pos] != '"')
    {
        if (body[pos] == '\\' && pos + 1 < body.size())
        {
            pos++;
            if (body[pos] == 'n') result += '\n';
            else result += body[pos];
        }
        else
        {
            result += body[pos];
        }
        pos++;
    }

    return result;
}

float HttpServer::extractJsonNumberField(const string &body, const string &key) const
{
    string pattern = "\"" + key + "\"";
    size_t pos = body.find(pattern);
    if (pos == string::npos) return 0.0f;

    pos = body.find(':', pos);
    if (pos == string::npos) return 0.0f;
    pos++;

    while (pos < body.size() && isspace(static_cast<unsigned char>(body[pos]))) pos++;

    size_t start = pos;
    while (pos < body.size() && (isdigit(static_cast<unsigned char>(body[pos])) || body[pos] == '.' || body[pos] == '-'))
    {
        pos++;
    }

    string numStr = body.substr(start, pos - start);
    if (numStr.empty()) return 0.0f;

    return static_cast<float>(atof(numStr.c_str()));
}

string HttpServer::buildResponse(int statusCode, const string &statusText,
                                   const string &contentType, const string &body) const
{
    ostringstream oss;
    oss << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";
    oss << "Content-Type: " << contentType << "\r\n";
    oss << "Content-Length: " << body.size() << "\r\n";
    oss << "Access-Control-Allow-Origin: *\r\n";
    oss << "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n";
    oss << "Access-Control-Allow-Headers: Content-Type\r\n";
    oss << "Connection: close\r\n";
    oss << "\r\n";
    oss << body;
    return oss.str();
}

void HttpServer::handleClient(unsigned long long clientSocketRaw)
{
    SOCKET clientSocket = static_cast<SOCKET>(clientSocketRaw);

    char buffer[8192];
    string rawRequest;

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';
        rawRequest = string(buffer, bytesReceived);
    }

    Request req = parseRequest(rawRequest);
    string response;

    if (req.method == "OPTIONS")
    {
        response = buildResponse(204, "No Content", "text/plain", "");
    }
    else if (req.method == "GET" && req.path == "/api/jobs")
    {
        response = buildResponse(200, "OK", "application/json", jobManager.getJobsJson());
    }
    else if (req.method == "GET" && req.path == "/api/dashboard")
    {
        response = buildResponse(200, "OK", "application/json", jobManager.getDashboardJson());
    }
    else if (req.method == "POST" && req.path == "/api/jobs")
    {
        int id = static_cast<int>(extractJsonNumberField(req.body, "jobId"));
        string company = extractJsonStringField(req.body, "companyName");
        string role = extractJsonStringField(req.body, "role");
        string description = extractJsonStringField(req.body, "jobDescription");
        string skills = extractJsonStringField(req.body, "requiredSkills");
        string ctc = extractJsonStringField(req.body, "packageCTC");
        string location = extractJsonStringField(req.body, "location");
        string employmentType = extractJsonStringField(req.body, "employmentType");
        float minCGPA = extractJsonNumberField(req.body, "minCGPA");
        string eligibleBranches = extractJsonStringField(req.body, "eligibleBranches");
        string deadline = extractJsonStringField(req.body, "deadline");
        string applicationLink = extractJsonStringField(req.body, "applicationLink");
        string source = extractJsonStringField(req.body, "source");
        string resumeUsed = extractJsonStringField(req.body, "resumeUsed");
        string status = extractJsonStringField(req.body, "status");
        string interviewRound = extractJsonStringField(req.body, "interviewRound");
        string notes = extractJsonStringField(req.body, "notes");
        string dateAdded = extractJsonStringField(req.body, "dateAdded");

        Job newJob(id, company, role, description, skills, ctc, location, employmentType,
                   minCGPA, eligibleBranches, deadline, applicationLink, source, resumeUsed,
                   status, interviewRound, notes, dateAdded);

        jobManager.addJobFromApi(newJob);
        response = buildResponse(201, "Created", "application/json", "{\"success\":true}");
    }
    else if (req.method == "PUT" && req.path == "/api/jobs")
    {
        int id = atoi(getQueryParam(req.query, "id").c_str());
        string newStatus = extractJsonStringField(req.body, "status");

        bool ok = jobManager.updateStatusById(id, newStatus);
        if (ok)
            response = buildResponse(200, "OK", "application/json", "{\"success\":true}");
        else
            response = buildResponse(404, "Not Found", "application/json", "{\"success\":false,\"error\":\"Job not found\"}");
    }
    else if (req.method == "DELETE" && req.path == "/api/jobs")
    {
        int id = atoi(getQueryParam(req.query, "id").c_str());

        bool ok = jobManager.deleteById(id);
        if (ok)
            response = buildResponse(200, "OK", "application/json", "{\"success\":true}");
        else
            response = buildResponse(404, "Not Found", "application/json", "{\"success\":false,\"error\":\"Job not found\"}");
    }
    else
    {
        response = buildResponse(404, "Not Found", "application/json", "{\"error\":\"Unknown endpoint\"}");
    }

    send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0);
}

void HttpServer::start(int port)
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed.\n";
        return;
    }
#endif

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        cout << "Error creating socket.\n";
        return;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(static_cast<unsigned short>(port));

    if (bind(listenSocket, reinterpret_cast<sockaddr *>(&service), sizeof(service)) == SOCKET_ERROR)
    {
        cout << "Bind failed. Is port " << port << " already in use?\n";
        closesocket(listenSocket);
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen failed.\n";
        closesocket(listenSocket);
        return;
    }

    cout << "Placement Tracker API server running at http://localhost:" << port << "\n";
    cout << "Open frontend/index.html in your browser to use the UI.\n";
    cout << "Press Ctrl+C to stop the server.\n";

    while (true)
    {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET)
        {
            continue;
        }

        handleClient(static_cast<unsigned long long>(clientSocket));
        closesocket(clientSocket);
    }

#ifdef _WIN32
    WSACleanup();
#endif
}
