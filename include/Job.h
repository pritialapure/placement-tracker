#ifndef JOB_H
#define JOB_H

#include <string>
#include <fstream>
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
    string getLocation() const;
    string getPackageCTC() const;
    string getEmploymentType() const;
    float getMinCGPA() const;
    string getEligibleBranches() const;
    string getApplicationLink() const;
    string getSource() const;
    string getResumeUsed() const;
    string getInterviewRound() const;
    string getNotes() const;
    string getDateAdded() const;
    string getLastUpdated() const;
    string getJobDescription() const;
    string getRequiredSkills() const;

public:
    Job();

    // Input & Display
    void inputJobDetails();
    void displayJobSummary() const;
    void displayJobDetails() const;

    // Getters
    int getJobId() const;
    string getCompanyName() const;
    string getRole() const;
    string getStatus() const;
    string getDeadline() const;

    // Setters
    void setStatus(const string &newStatus);
    void setInterviewRound(const string &round);
    void setNotes(const string &newNotes);
    void setLastUpdated(const string &date);

    // File Handling
    void saveToFile(ofstream &out) const;
    void loadFromFile(ifstream &in);
    void updateJob();
};

#endif