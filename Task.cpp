#include "Task.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>

Task::Task(const std::string& taskName, bool isForAdult, int taskPoints, int taskFrequency) :
    taskName(taskName), isForAdult(isForAdult), taskPoints(taskPoints) , taskFrequency(taskFrequency) {}

void Task::display() const {
    std::cout << "Name: " << taskName
        << ", Adult: " << (isForAdult ? "Yes" : "No")
        << ", Points: " << taskPoints
        << ", Frequency: " << taskFrequency
        << std::endl;
};

void Task::SaveData(const std::vector<Task>& tasks) {
    std::ofstream outFile("tasks.txt");
    if (outFile.is_open()) {
        for (const auto& task : tasks) {
            outFile << task.taskName << ","
                << task.isForAdult << ","
                << task.taskPoints << ","
				<< task.taskFrequency << "\n";
        }
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

std::vector<Task> Task::LoadData() {
    std::vector<Task> tasks;
    std::ifstream inFile("tasks.txt");
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string taskName;
            bool isForAdult;
            int taskPoints;
            int taskFrequency;

            std::getline(iss, taskName, ',');
            iss >> isForAdult;
            iss.ignore(1); // Ignorování èárky
            iss >> taskPoints;
            iss.ignore(1); // Ignorování èárky
            iss >> taskFrequency;


            tasks.emplace_back(taskName, isForAdult, taskPoints,taskFrequency);
        }
        inFile.close();
    }
    else {
        std::cerr << "Unable to open file for reading." << std::endl;
    }

    return tasks;
}