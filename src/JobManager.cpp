#include "../include/JobManager.h"

#include <iostream>
#include <fstream>

using namespace std;

JobManager::JobManager()
{
    loadJobsFromFile();
}

void JobManager::addJob()
{
    Job job;

    job.inputJobDetails();

    jobs.push_back(job);

    cout << "\nJob added successfully.\n";

    saveJobsToFile();
}
void JobManager::displayAllJobs() const
{
    if (jobs.empty())
    {
        cout << "\nNo placement opportunities found.\n";
        return;
    }

    cout << "\n==============================================================\n";
    cout << "                    Placement Opportunities\n";
    cout << "==============================================================\n";

    for (const Job &job : jobs)
    {
        job.displayJobDetails();
    }

    cout << "\nTotal Jobs : " << jobs.size() << endl;
}