#ifndef JOB_MANAGER_H
#define JOB_MANAGER_H

#include "Job.h"
#include <vector>

using namespace std;

class JobManager
{
private:
    vector<Job> jobs;

public:
    JobManager();

    // CRUD Operations
    void addJob();
    void displayAllJobs() const;
    void searchByCompany() const;
    void searchByStatus() const;
    void searchByJobId() const;
    void updateJobStatus();
    void deleteJob();

    // Dashboard
    void showDashboard() const;

    // File Handling
    void saveJobsToFile() const;
    void loadJobsFromFile();
};

#endif