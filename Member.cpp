#include "Member.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>

Member::Member(const std::string& name, bool adult, int points, const std::string& id, const std::string& phoneNumber)
    : name(name), isAdult(adult), points(points), id(id), phoneNumber(phoneNumber) {}

void Member::display() const {
    std::cout << "Name: " << name
        << ", Adult: " << (isAdult ? "Yes" : "No")
        << ", Points: " << points
        << ", ID: " << id
        << ", Phone Number: " << phoneNumber
        << std::endl;
};

void Member::SaveData(const std::vector<Member>& members) {
    std::cout << members[0].name << members[0].isAdult << members[0].points << members[0].id << members[0].phoneNumber << std::endl;
    std::ofstream outFile("members.txt");
    if (outFile.is_open()) {
        for (const auto& member : members) {
            outFile << member.name << ","
                << member.isAdult << ","
                << member.points << ","
                << member.id << ","
                << member.phoneNumber << "\n";
        }
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

std::vector<Member> Member::LoadData() {
    std::vector<Member> members;
    std::ifstream inFile("members.txt");
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name, id, phoneNumber;
            bool isAdult;
            int points;

            std::getline(iss, name, ',');
            iss >> isAdult;
            iss.ignore(1); // Ignorování èárky
            iss >> points;
            iss.ignore(1); // Ignorování èárky
            std::getline(iss, id, ',');
            std::getline(iss, phoneNumber);

            members.emplace_back(name, isAdult, points, id, phoneNumber);
        }
        inFile.close();
    }
    else {
        std::cerr << "Unable to open file for reading." << std::endl;
    }

    return members;
}