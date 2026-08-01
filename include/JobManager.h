#ifndef JOB_MANAGER_H
#define JOB_MANAGER_H

#include "Job.h"
#include <vector>
#include <string>

class JobManager
{
private:
    std::vector<Job> jobs;

public:
    JobManager();

    // CRUD Operations (console)
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

    // API support (used by HttpServer; does not touch the console flow above)
    std::string getJobsJson() const;
    std::string getDashboardJson() const;
    bool addJobFromApi(const Job &newJob);
    bool updateStatusById(int id, const std::string &newStatus);
    bool deleteById(int id);
};

#endif
