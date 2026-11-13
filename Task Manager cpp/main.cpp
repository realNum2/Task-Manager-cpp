#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Task.h"

using namespace std;

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    vector<Task> tasks;
    loadTask(tasks);

    while (true)
    {
        printMenu();

        int action;
        cin >> action;
        cin.ignore();

        if (action == 0) {
            saveTask(tasks);
            cout << "Bye!\n";
            break;
        }

        switch (action)
        {
        case 1: addTask(tasks); saveTask(tasks); break;
        case 2: showAllTasks(tasks); break;
        case 3: showActiveTask(tasks); break;
        case 4: completeTask(tasks); saveTask(tasks); break;
        case 5: deleteTask(tasks); saveTask(tasks); break;
        default: cout << "Unknown operation :/\n"; break;
        }
    }

    return 0;
}