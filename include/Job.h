#ifndef JOB_H
#define JOB_H

#include <string>

using namespace std;

class Job
{
private:
    int jobId;
    string companyName;
    string role;
    string jobDescription;
    string requiredSkills;
    string packageCTC;
    string location;
    string employmentType;
    float minCGPA;
    string eligibleBranches;
    string deadline;
    string applicationLink;
    string source;
    string resumeUsed;
    string status;
    string interviewRound;
    string notes;
    string dateAdded;
    string lastUpdated;

public:
    Job();

    void inputJobDetails();
    void displayJobSummary() const;
    void displayJobDetails() const;
};

#endif