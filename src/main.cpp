#include "../include/JobManager.h"

#include <iostream>
#include <limits>

using namespace std;

int main()
{
    JobManager manager;
    int choice;

    do
    {
        cout << "\n";
        cout << "=====================================================\n";
        cout << "             PLACEMENT TRACKER SYSTEM\n";
        cout << "=====================================================\n";
        cout << "1. Add New Job\n";
        cout << "2. View All Jobs\n";
        cout << "3. Search Job By Company\n";
        cout << "4. Search Job By Status\n";
        cout << "5. Search Job By ID\n";
        cout << "6. Update Job Status\n";
        cout << "7. Delete Job\n";
        cout << "8. Dashboard\n";
        cout << "9. Save Jobs\n";
        cout << "10. Load Jobs\n";
        cout << "0. Exit\n";
        cout << "=====================================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "\nInvalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // sentinel so switch falls to default
            continue;
        }

        switch (choice)
        {
        case 1:
            manager.addJob();
            break;
        case 2:
            manager.displayAllJobs();
            break;
        case 3:
            manager.searchByCompany();
            break;
        case 4:
            manager.searchByStatus();
            break;
        case 5:
            manager.searchByJobId();
            break;
        case 6:
            manager.updateJobStatus();
            break;
        case 7:
            manager.deleteJob();
            break;
        case 8:
            manager.showDashboard();
            break;
        case 9:
            manager.saveJobsToFile();
            cout << "\nJobs saved successfully.\n";
            break;
        case 10:
            manager.loadJobsFromFile();
            cout << "\nJobs loaded successfully.\n";
            break;
        case 0:
            manager.saveJobsToFile();
            cout << "\nThank you for using Placement Tracker!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
