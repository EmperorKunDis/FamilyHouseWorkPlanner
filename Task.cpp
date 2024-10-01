#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>


void saveTaskToFile(const std::vector<Task>& tasks, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << tasks.size();

	for (const Task& task : tasks) {
		std::string description = task.taskDescription;
		std::string name = task.taskName;
		int points = task.taskPoints;
		int frequency = task.taskFrequency;
		bool adult = task.isForAdult;
		std::replace(description.begin(), description.end(), ' ', '_');

		ostream << '\n' << name << ' ' << description << ' ' << points << ' ' << frequency;
	}
}

std::vector<Task> loadTasksFromFile(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<Task>();
	}
	std::vector<Task> tasks;
	std::ifstream istream(fileName);

	int n;
	istream >> n;
	for (int i = 0; i < n; i++) {
		std::string description;
		std::string name;
		int points;
		int frequency;
		bool adult;
		istream >> name >> description >> points >> frequency >> adult;
		std::replace(name.begin(), name.end(), '_', ' ');
		tasks.push_back(Task{name, description, points, frequency});
	}

	return tasks;
}