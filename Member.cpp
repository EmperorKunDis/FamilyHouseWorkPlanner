#include "Member.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveMembersToFile(const std::vector<Member>& members, const std::string& fileMemberName)
{
	std::ofstream ostream(fileMemberName);
	ostream << members.size();

	for (const Member& member : members) {
		std::string name = member.memberName;
		bool adult = member.isAdult;

		ostream << '\n' << name << ' ' << adult;
	}
}

std::vector<Member> loadMembersFromFile(const std::string& fileMemberName) {
	if (!std::filesystem::exists(fileMemberName)) {
		return std::vector<Member>();
	}
	std::vector<Member> members;
	std::ifstream istream(fileMemberName);

	int n;
	istream >> n;

	for (int i = 0; i < n; i++) {
		std::string name;
		bool adult;
		istream >> name >> adult;
		members.push_back(Member{ name, adult });
	}

	return members;	
}
