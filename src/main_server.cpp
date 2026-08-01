#include "../include/JobManager.h"
#include "../include/HttpServer.h"

int main()
{
    JobManager manager;   // loads existing jobs.txt on construction, same as console app
    HttpServer server(manager);
    server.start(8080);
    return 0;
}
