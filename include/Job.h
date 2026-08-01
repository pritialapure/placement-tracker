#ifndef JOB_H
#define JOB_H

#include <string>
#include <fstream>

class Job
{
private:
    int jobId;
    std::string companyName;
    std::string role;
    std::string jobDescription;
    std::string requiredSkills;
    std::string packageCTC;
    std::string location;
    std::string employmentType;
    float minCGPA;
    std::string eligibleBranches;
    std::string deadline;
    std::string applicationLink;
    std::string source;
    std::string resumeUsed;
    std::string status;
    std::string interviewRound;
    std::string notes;
    std::string dateAdded;
    std::string lastUpdated;

public:
    Job();

    // Used by the API layer (HttpServer) to build a Job from parsed JSON
    // fields, without touching the console-based inputJobDetails() flow.
    Job(int id, const std::string &company, const std::string &role,
        const std::string &description, const std::string &skills,
        const std::string &ctc, const std::string &location,
        const std::string &employmentType, float minCGPA,
        const std::string &eligibleBranches, const std::string &deadline,
        const std::string &applicationLink, const std::string &source,
        const std::string &resumeUsed, const std::string &status,
        const std::string &interviewRound, const std::string &notes,
        const std::string &dateAdded);

    // Input & Display
    void inputJobDetails();
    void displayJobSummary() const;
    void displayJobDetails() const;

    // Getters
    int getJobId() const;
    std::string getCompanyName() const;
    std::string getRole() const;
    std::string getStatus() const;
    std::string getDeadline() const;

    // Setters
    void setStatus(const std::string &newStatus);
    void setInterviewRound(const std::string &round);
    void setNotes(const std::string &newNotes);
    void setLastUpdated(const std::string &date);

    // File Handling
    void saveToFile(std::ofstream &out) const;
    void loadFromFile(std::ifstream &in);

    // API support
    std::string toJson() const;
};

#endif
