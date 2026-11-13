#pragma once
#include <vector>
#include <string>
using namespace std;

struct Task {
	string task;
	bool isCompleted = false;
	int priority;
};

void printMenu();
void addTask(vector<Task>& tasks);
void showAllTasks(const vector<Task>& tasks);
void showActiveTask(const vector<Task>& tasks);
void completeTask(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void saveTask(const vector<Task>& tasks);
void loadTask(vector<Task>& tasks);