#pragma once
#include <string>
#include <vector>

class Task
{
public:
	Task(const std::string& taskName, bool isForAdult, int taskPoints, int taskFrequency);
	void display() const;
	static void SaveData(const std::vector<Task>& tasks);
	static std::vector<Task> LoadData(); std::string taskName;
	bool isForAdult;
	int taskPoints;
	int taskFrequency;	
};