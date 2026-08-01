# Placement Tracker

A C++ console application to track campus placement job applications — company, role, status, deadlines, and interview rounds — with file-based persistence. Includes an optional HTTP API and web UI for a browser-based view of the same data.

## Features
- Add, view, search, update, and delete job applications
- Search by company, status, or job ID
- Dashboard with status breakdown
- File-based persistence (`data/jobs.txt`)
- Optional web UI backed by a built-in HTTP API

## Tech Stack
C++17, OOP, STL — HTML/CSS/JS for the web UI

## Build & Run

**Console app:**
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Job.cpp src/JobManager.cpp -o placement_tracker.exe
./placement_tracker.exe
```

**Web UI:**
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/main_server.cpp src/Job.cpp src/JobManager.cpp src/HttpServer.cpp -o placement_server.exe -lws2_32
./placement_server.exe
```
Then open `frontend/index.html` in your browser.
