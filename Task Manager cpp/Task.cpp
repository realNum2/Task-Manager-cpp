#include "Task.h"
#include <iostream>
#include <fstream>

using namespace std;

void printMenu()
{
    cout << "\n=== Task Manager ===" << endl;
    cout << "────────────────────────────────────────────" << endl;
    cout << "[1] Add task\n";
    cout << "[2] Show all tasks\n";
    cout << "[3] Show only active tasks\n";
    cout << "[4] Mark task as completed\n";
    cout << "[5] Delete task\n";
    cout << "[0] Exit\n";
    cout << "────────────────────────────────────────────" << endl;
    cout << "Your choice: ";
}

void addTask(vector <Task>& tasks)
{
    Task newTask;

    cout << "Enter task: ";
    getline(cin, newTask.task);

    cout << "What priority of your task (1, 2, 3)? ";
    cin >> newTask.priority;
    cin.ignore();
    if (newTask.priority < 1 || newTask.priority > 3) {
        newTask.priority = 2;
    }

    newTask.isCompleted = false;

    tasks.push_back(newTask);
    cout << "Task Added!" << endl;
}

void showAllTasks(const vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "Task list is empty :(" << endl;
    }
    else
    {
        for (int i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". "
                << (tasks[i].isCompleted ? " [X] " : " [] ")
                << tasks[i].task << " Priority: " << tasks[i].priority << endl;
        }
    }
}

void showActiveTask(const vector<Task>& tasks)
{
    for (int i = 0; i < tasks.size(); ++i)
    {
        if (!tasks[i].isCompleted)
        {
            cout << i + 1 << ". "
                << tasks[i].task << " Priority: " << tasks[i].priority << endl;
        } 
        if (tasks[i].isCompleted)
        {
            cout << "No active tasks yet" << endl;
        }
    }
}

void completeTask(vector<Task>& tasks)
{
    if (tasks.empty()) {
        cout << "No tasks to complete.\n";
        return;
    }

    cout << "This is all your Tasks: " << endl;

    for (int i = 0; i < tasks.size(); ++i)
    {
        if (!tasks[i].isCompleted)
        {
            cout << i + 1 << ". " << tasks[i].task << " Priority: " << tasks[i].priority << endl;
        }
        if (tasks[i].isCompleted)
        {
            cout << "No active tasks yet" << endl;
        }
    }
    int choice;
    cout << "Which Task you wanna complete? ";
    cin >> choice;
    cin.ignore();
    int index = choice - 1;

    if (index >= 0 && index < static_cast<int>(tasks.size())) {
        tasks[index].isCompleted = true;
        cout << "Task \"" << tasks[index].task << "\" is Completed!" << endl;
    }
    else
    {
        cout << "Error: task does not exist!" << endl;
    }
}

void deleteTask(vector<Task>& tasks)
{
    //===OUTPUT===
    if (tasks.empty())
    {
        cout << "Task list is empty :(" << endl;
        return;
    }

    cout << "This is all your Tasks: " << endl;
    
    for (int i = 0; i < tasks.size(); ++i)
    {
        cout << i + 1 << ". "
            << (tasks[i].isCompleted ? " [X] " : " [] ")
            << tasks[i].task << " | Priority: " << tasks[i].priority << endl;
    }

    //===INPUT===
    int choice; 
    cout << "Which Task you wanna delete? ";
    cin >> choice; cin.ignore();
    int index = choice - 1;

    //===DELETE LOGIC===
    if (index >= 0 && index < static_cast<int>(tasks.size()))
    {
        cout << "Task \"" << tasks[index].task << "\" is Deleted!" << endl;
        tasks.erase(tasks.begin() + index);
    }
    else
    {
        cout << "Error: This task does not exist!" << endl;
    }
}

void saveTask(const vector<Task>& tasks)
{
    ofstream out("tasks.txt");
    if (!out.is_open()) 
    {
        cout << "Error opening file!" << endl;
        return;
    }

    for (const auto& t : tasks)
    {
        out << t.isCompleted << "|" << t.task << "|" << t.priority << "\n";
    }
}

void loadTask(vector<Task>& tasks)
{
    ifstream in("tasks.txt");
    if (!in.is_open()) return;
    tasks.clear();

    string line;

    while (getline(in, line))
    {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find('|', pos1 + 1);
        if (pos2 == string::npos) continue;

        bool isCompleted = (line.substr(0, pos1) == "1");
        string text = line.substr(pos1 + 1, pos2 - pos1 - 1);
        int priority = stoi(line.substr(pos2 + 1));

        tasks.push_back({ text, isCompleted, priority });
    }
    cout << "Task loaded!" << endl;
}