#include "../include/Job.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

Job::Job()
{
    jobId = 0;
    companyName = "";
    role = "";
    jobDescription = "";
    requiredSkills = "";
    packageCTC = "";
    location = "";
    employmentType = "";
    minCGPA = 0.0;
    eligibleBranches = "";
    deadline = "";
    applicationLink = "";
    source = "";
    resumeUsed = "";
    status = "Not Applied";
    interviewRound = "None";
    notes = "";
    dateAdded = "";
    lastUpdated = "";
}

Job::Job(int id, const string &company, const string &role_, const string &description,
          const string &skills, const string &ctc, const string &location_,
          const string &employmentType_, float minCGPA_, const string &eligibleBranches_,
          const string &deadline_, const string &applicationLink_, const string &source_,
          const string &resumeUsed_, const string &status_, const string &interviewRound_,
          const string &notes_, const string &dateAdded_)
{
    jobId = id;
    companyName = company;
    role = role_;
    jobDescription = description;
    requiredSkills = skills;
    packageCTC = ctc;
    location = location_;
    employmentType = employmentType_;
    minCGPA = minCGPA_;
    eligibleBranches = eligibleBranches_;
    deadline = deadline_;
    applicationLink = applicationLink_;
    source = source_;
    resumeUsed = resumeUsed_;
    status = status_.empty() ? "Not Applied" : status_;
    interviewRound = interviewRound_.empty() ? "None" : interviewRound_;
    notes = notes_;
    dateAdded = dateAdded_;
    lastUpdated = dateAdded_;
}

void Job::inputJobDetails()
{
    cout << "\n========== Add New Job ==========\n";

    cout << "Job ID: ";
    while (!(cin >> jobId))
    {
        cout << "Invalid input. Please enter a numeric Job ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Company Name: ";
    getline(cin, companyName);

    cout << "Role: ";
    getline(cin, role);

    cout << "Job Description: ";
    getline(cin, jobDescription);

    cout << "Required Skills: ";
    getline(cin, requiredSkills);

    cout << "Package (CTC): ";
    getline(cin, packageCTC);

    cout << "Location: ";
    getline(cin, location);

    cout << "Employment Type: ";
    getline(cin, employmentType);

    cout << "Minimum CGPA: ";
    while (!(cin >> minCGPA))
    {
        cout << "Invalid input. Please enter a numeric CGPA: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Eligible Branches: ";
    getline(cin, eligibleBranches);

    cout << "Application Deadline: ";
    getline(cin, deadline);

    cout << "Application Link: ";
    getline(cin, applicationLink);

    cout << "Source (Email / LinkedIn / TPO): ";
    getline(cin, source);

    cout << "Resume Used: ";
    getline(cin, resumeUsed);

    cout << "Status: ";
    getline(cin, status);

    cout << "Interview Round: ";
    getline(cin, interviewRound);

    cout << "Notes: ";
    getline(cin, notes);

    cout << "Date Added: ";
    getline(cin, dateAdded);

    lastUpdated = dateAdded;

    cout << "\nJob Added Successfully!\n";
}

void Job::displayJobSummary() const
{
    cout << left
         << setw(8) << jobId
         << setw(25) << companyName
         << setw(25) << role
         << setw(18) << status
         << deadline
         << endl;
}

void Job::displayJobDetails() const
{
    cout << "\n=========================================\n";
    cout << "Company           : " << companyName << endl;
    cout << "Role              : " << role << endl;
    cout << "Description       : " << jobDescription << endl;
    cout << "Skills            : " << requiredSkills << endl;
    cout << "Package           : " << packageCTC << endl;
    cout << "Location          : " << location << endl;
    cout << "Employment Type   : " << employmentType << endl;
    cout << "Minimum CGPA      : " << minCGPA << endl;
    cout << "Eligible Branches : " << eligibleBranches << endl;
    cout << "Deadline          : " << deadline << endl;
    cout << "Application Link  : " << applicationLink << endl;
    cout << "Source            : " << source << endl;
    cout << "Resume Used       : " << resumeUsed << endl;
    cout << "Status            : " << status << endl;
    cout << "Interview Round   : " << interviewRound << endl;
    cout << "Notes             : " << notes << endl;
    cout << "Date Added        : " << dateAdded << endl;
    cout << "Last Updated      : " << lastUpdated << endl;
    cout << "=========================================\n";
}

int Job::getJobId() const { return jobId; }
string Job::getCompanyName() const { return companyName; }
string Job::getRole() const { return role; }
string Job::getStatus() const { return status; }
string Job::getDeadline() const { return deadline; }

void Job::setStatus(const string &newStatus) { status = newStatus; }
void Job::setInterviewRound(const string &round) { interviewRound = round; }
void Job::setNotes(const string &newNotes) { notes = newNotes; }
void Job::setLastUpdated(const string &date) { lastUpdated = date; }

void Job::saveToFile(ofstream &out) const
{
    out << jobId << endl;
    out << companyName << endl;
    out << role << endl;
    out << jobDescription << endl;
    out << requiredSkills << endl;
    out << packageCTC << endl;
    out << location << endl;
    out << employmentType << endl;
    out << minCGPA << endl;
    out << eligibleBranches << endl;
    out << deadline << endl;
    out << applicationLink << endl;
    out << source << endl;
    out << resumeUsed << endl;
    out << status << endl;
    out << interviewRound << endl;
    out << notes << endl;
    out << dateAdded << endl;
    out << lastUpdated << endl;
    out << "------------------------" << endl;
}

void Job::loadFromFile(ifstream &in)
{
    in >> jobId;
    in.ignore();

    getline(in, companyName);
    getline(in, role);
    getline(in, jobDescription);
    getline(in, requiredSkills);
    getline(in, packageCTC);
    getline(in, location);
    getline(in, employmentType);

    in >> minCGPA;
    in.ignore();

    getline(in, eligibleBranches);
    getline(in, deadline);
    getline(in, applicationLink);
    getline(in, source);
    getline(in, resumeUsed);
    getline(in, status);
    getline(in, interviewRound);
    getline(in, notes);
    getline(in, dateAdded);
    getline(in, lastUpdated);

    string separator;
    getline(in, separator);
}

// Escapes characters that would otherwise break JSON string syntax
// (double quotes, backslashes, and raw newlines from free-text fields
// like notes/jobDescription).
static string jsonEscape(const string &input)
{
    string output;
    output.reserve(input.size());

    for (char c : input)
    {
        switch (c)
        {
        case '"':
            output += "\\\"";
            break;
        case '\\':
            output += "\\\\";
            break;
        case '\n':
            output += "\\n";
            break;
        case '\r':
            break; // drop carriage returns
        default:
            output += c;
        }
    }

    return output;
}

string Job::toJson() const
{
    ostringstream oss;
    oss << "{"
        << "\"jobId\":" << jobId << ","
        << "\"companyName\":\"" << jsonEscape(companyName) << "\","
        << "\"role\":\"" << jsonEscape(role) << "\","
        << "\"jobDescription\":\"" << jsonEscape(jobDescription) << "\","
        << "\"requiredSkills\":\"" << jsonEscape(requiredSkills) << "\","
        << "\"packageCTC\":\"" << jsonEscape(packageCTC) << "\","
        << "\"location\":\"" << jsonEscape(location) << "\","
        << "\"employmentType\":\"" << jsonEscape(employmentType) << "\","
        << "\"minCGPA\":" << minCGPA << ","
        << "\"eligibleBranches\":\"" << jsonEscape(eligibleBranches) << "\","
        << "\"deadline\":\"" << jsonEscape(deadline) << "\","
        << "\"applicationLink\":\"" << jsonEscape(applicationLink) << "\","
        << "\"source\":\"" << jsonEscape(source) << "\","
        << "\"resumeUsed\":\"" << jsonEscape(resumeUsed) << "\","
        << "\"status\":\"" << jsonEscape(status) << "\","
        << "\"interviewRound\":\"" << jsonEscape(interviewRound) << "\","
        << "\"notes\":\"" << jsonEscape(notes) << "\","
        << "\"dateAdded\":\"" << jsonEscape(dateAdded) << "\","
        << "\"lastUpdated\":\"" << jsonEscape(lastUpdated) << "\""
        << "}";
    return oss.str();
}
