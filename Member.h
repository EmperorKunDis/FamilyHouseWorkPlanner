#pragma once
#include <string>
#include <vector>

struct Member
{
	std::string memberName;
	bool isAdult;
	std::vector<std::string> members;
};

void saveMembersToFile(const std::vector<Member>& Members, const std::string& fileMemberName);
std::vector<Member> loadMembersFromFile(const std::string& fileMemberName);