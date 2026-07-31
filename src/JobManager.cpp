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
void JobManager::searchByCompany() const
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    string company;
    cout << "\nEnter Company Name: ";
    cin.ignore();
    getline(cin, company);

    bool found = false;

    for (const Job &job : jobs)
    {
        if (job.getCompanyName() == company)
        {
            job.displayJobDetails();
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo jobs found for " << company << endl;
    }
}

void JobManager::searchByStatus() const
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    string status;
    cout << "\nEnter Status: ";
    cin.ignore();
    getline(cin, status);

    bool found = false;

    for (const Job &job : jobs)
    {
        if (job.getStatus() == status)
        {
            job.displayJobDetails();
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo jobs found with status " << status << endl;
    }
}

void JobManager::searchByJobId() const
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    int id;

    cout << "\nEnter Job ID: ";
    cin >> id;

    bool found = false;

    for (const Job &job : jobs)
    {
        if (job.getJobId() == id)
        {
            job.displayJobDetails();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nJob not found.\n";
    }
}

void JobManager::updateJobStatus()
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    int id;
    cout << "\nEnter Job ID: ";
    cin >> id;
    cin.ignore();

    bool found = false;

    for (Job &job : jobs)
    {
        if (job.getJobId() == id)
        {
            string newStatus;

            cout << "\nEnter New Status\n";
            cout << "Examples:\n";
            cout << "Not Applied\n";
            cout << "Applied\n";
            cout << "OA Scheduled\n";
            cout << "OA Completed\n";
            cout << "Technical Interview\n";
            cout << "HR Interview\n";
            cout << "Selected\n";
            cout << "Rejected\n";
            cout << "Offer Accepted\n";
            cout << "Offer Declined\n\n";

            cout << "Status: ";
            getline(cin, newStatus);

            job.setStatus(newStatus);

            saveJobsToFile();

            cout << "\nStatus updated successfully.\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nJob not found.\n";
    }
}

void JobManager::deleteJob()
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    int id;

    cout << "\nEnter Job ID to delete: ";
    cin >> id;

    for (auto it = jobs.begin(); it != jobs.end(); ++it)
    {
        if (it->getJobId() == id)
        {
            jobs.erase(it);

            saveJobsToFile();

            cout << "\nJob deleted successfully.\n";
            return;
        }
    }

    cout << "\nJob not found.\n";
}
void JobManager::saveJobsToFile() const
{
    ofstream outFile("../data/jobs.txt");

    if (!outFile)
    {
        cout << "\nError opening file for writing.\n";
        return;
    }

    for (const Job &job : jobs)
    {
        job.saveToFile(outFile);
    }

    outFile.close();
}

void JobManager::loadJobsFromFile()
{
    ifstream inFile("../data/jobs.txt");

    if (!inFile)
    {
        return;
    }

    jobs.clear();

    while (inFile.peek() != EOF)
    {
        Job job;

        job.loadFromFile(inFile);

        if (inFile)
        {
            jobs.push_back(job);
        }
    }

    inFile.close();
}
void JobManager::showDashboard() const
{
    if (jobs.empty())
    {
        cout << "\nNo jobs available.\n";
        return;
    }

    int totalJobs = jobs.size();
    int notApplied = 0;
    int applied = 0;
    int oaScheduled = 0;
    int oaCompleted = 0;
    int technicalInterview = 0;
    int hrInterview = 0;
    int selected = 0;
    int rejected = 0;
    int offerAccepted = 0;
    int offerDeclined = 0;

    for (const Job &job : jobs)
    {
        string status = job.getStatus();

        if (status == "Not Applied")
            notApplied++;
        else if (status == "Applied")
            applied++;
        else if (status == "OA Scheduled")
            oaScheduled++;
        else if (status == "OA Completed")
            oaCompleted++;
        else if (status == "Technical Interview")
            technicalInterview++;
        else if (status == "HR Interview")
            hrInterview++;
        else if (status == "Selected")
            selected++;
        else if (status == "Rejected")
            rejected++;
        else if (status == "Offer Accepted")
            offerAccepted++;
        else if (status == "Offer Declined")
            offerDeclined++;
    }

    cout << "\n";
    cout << "=============================================\n";
    cout << "         PLACEMENT TRACKER DASHBOARD\n";
    cout << "=============================================\n";

    cout << "Total Opportunities      : " << totalJobs << endl;
    cout << "Not Applied              : " << notApplied << endl;
    cout << "Applied                  : " << applied << endl;
    cout << "OA Scheduled             : " << oaScheduled << endl;
    cout << "OA Completed             : " << oaCompleted << endl;
    cout << "Technical Interview      : " << technicalInterview << endl;
    cout << "HR Interview             : " << hrInterview << endl;
    cout << "Selected                 : " << selected << endl;
    cout << "Rejected                 : " << rejected << endl;
    cout << "Offer Accepted           : " << offerAccepted << endl;
    cout << "Offer Declined           : " << offerDeclined << endl;

    cout << "=============================================\n";
}