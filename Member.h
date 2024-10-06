#pragma once
#include <string>
#include <vector>

class Member {
    public:
        Member(const std::string& name, bool isAdult, int points, const std::string& id, const std::string& phoneNumber);
        void display() const;
        static void SaveData(const std::vector<Member>& members);
        static std::vector<Member> LoadData();

    private:
        std::string name;
        bool isAdult;
        int points;
        std::string id;
        std::string phoneNumber;
};


