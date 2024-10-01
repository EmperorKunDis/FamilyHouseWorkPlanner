#pragma once
#include <string>
#include <vector>

struct Task
{
	std::string taskDescription;
	std::string taskName;
	int taskPoints;
	int taskFrequency;
	bool isForAdult;
	std::vector<std::string> subtasks;

};

void saveTaskToFile(const std::vector<Task>& tasks, const std::string& fileName);
std::vector<Task> loadTasksFromFile(const std::string& fileName);