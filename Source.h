#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <ctime>
#include <climits>
#include <cmath>

class Task {
public:
    std::string name;
    std::string frequency;
    std::string description;
    int points;

    Task(std::string n, std::string freq, std::string desc, int p)
        : name(n), frequency(freq), description(desc), points(p) {}

    bool operator==(const Task& other) const {
        return name == other.name && frequency == other.frequency &&
            description == other.description && points == other.points;
    }
};

class User {
public:
    std::string name;
    std::map<int, std::vector<Task>> tasks;  // day -> tasks
    std::map<int, int> weeklyPoints;  // week -> points
    int monthlyPoints;

    User(std::string n) : name(n), monthlyPoints(0) {}

    void addTask(int day, const Task& task) {
        tasks[day].push_back(task);
        int week = (day - 1) / 7 + 1;
        weeklyPoints[week] += task.points;
        monthlyPoints += task.points;
    }

    bool hasTaskOnDay(int day, const std::string& taskName) const {
        auto it = tasks.find(day);
        if (it != tasks.end()) {
            return std::any_of(it->second.begin(), it->second.end(),
                [&taskName](const Task& t) { return t.name == taskName; });
        }
        return false;
    }

    int getWeeklyPoints(int week) const {
        auto it = weeklyPoints.find(week);
        return (it != weeklyPoints.end()) ? it->second : 0;
    }
};

class TaskPlanner {
private:
    std::vector<Task> allTasks;
    std::vector<User> users;
    int startDay;
    std::mt19937 rng;

    int getWeekday(int day) const {
        return (startDay + day - 2) % 7;
    }

    User* findUserWithLeastPoints(int week) {
        return &*std::min_element(users.begin(), users.end(),
            [week](const User& a, const User& b) {
                return a.getWeeklyPoints(week) < b.getWeeklyPoints(week);
            });
    }

    void balanceMonthlyPoints() {
        while (true) {
            auto minMax = std::minmax_element(users.begin(), users.end(),
                [](const User& a, const User& b) { return a.monthlyPoints < b.monthlyPoints; });

            int diff = minMax.second->monthlyPoints - minMax.first->monthlyPoints;
            if (diff <= 5) break;  // Acceptable difference

            for (int day = 1; day <= 31; ++day) {
                auto& maxUserTasks = minMax.second->tasks[day];
                auto& minUserTasks = minMax.first->tasks[day];
                if (maxUserTasks.size() > minUserTasks.size()) {
                    Task taskToMove = maxUserTasks.back();
                    minMax.first->addTask(day, taskToMove);
                    minMax.second->monthlyPoints -= taskToMove.points;
                    minMax.second->weeklyPoints[(day - 1) / 7 + 1] -= taskToMove.points;
                    maxUserTasks.pop_back();
                    break;
                }
            }
        }
    }

public:
    TaskPlanner() : rng(std::time(0)) {
        users.push_back(User("Mom"));
        users.push_back(User("Dad"));
        users.push_back(User("Daughter"));
    }

    void addTask(const Task& task) {
        allTasks.push_back(task);
    }

    void setStartDay(int day) {
        startDay = day;
    }

    int getFrequency(const std::string& freq) {
        if (freq == "1/day") return 1;
        if (freq == "2/week") return 4;
        if (freq == "1/week") return 7;
        if (freq == "1/month") return 31;
        return 31;  // default to once a month
    }

    void distributeTasks() {
        std::shuffle(allTasks.begin(), allTasks.end(), rng);

        for (const auto& task : allTasks) {
            int frequency = getFrequency(task.frequency);
            for (int day = 1; day <= 31; day += frequency) {
                int weekday = getWeekday(day);
                if (weekday < 5) {  // Monday to Friday
                    int week = (day - 1) / 7 + 1;
                    User* minUser = findUserWithLeastPoints(week);
                    minUser->addTask(day, task);
                }
            }
        }

        // Distribute remaining tasks on weekends
        for (int day = 1; day <= 31; ++day) {
            int weekday = getWeekday(day);
            if (weekday >= 5) {  // Saturday or Sunday
                for (const auto& task : allTasks) {
                    if (std::none_of(users.begin(), users.end(), [&](const User& u) {
                        return u.hasTaskOnDay(day, task.name);
                        })) {
                        int week = (day - 1) / 7 + 1;
                        User* minUser = findUserWithLeastPoints(week);
                        minUser->addTask(day, task);
                    }
                }
            }
        }

        balanceMonthlyPoints();
    }

    void displayPlan() const {
        for (int day = 1; day <= 31; ++day) {
            std::cout << "Day " << day << " (" << (getWeekday(day) == 0 ? "Sunday" :
                getWeekday(day) == 1 ? "Monday" :
                getWeekday(day) == 2 ? "Tuesday" :
                getWeekday(day) == 3 ? "Wednesday" :
                getWeekday(day) == 4 ? "Thursday" :
                getWeekday(day) == 5 ? "Friday" : "Saturday") << "):\n";
            for (const auto& user : users) {
                std::cout << "  " << user.name << ":\n";
                auto it = user.tasks.find(day);
                if (it != user.tasks.end()) {
                    for (const auto& task : it->second) {
                        std::cout << "    - " << task.name << " (" << task.points << " points)\n";
                    }
                }
            }
            std::cout << "\n";
        }

        // Display weekly and monthly totals
        for (const auto& user : users) {
            std::cout << user.name << " totals:\n";
            for (const auto& weekPoints : user.weeklyPoints) {
                std::cout << "  Week " << weekPoints.first << ": " << weekPoints.second << " points\n";
            }
            std::cout << "  Monthly total: " << user.monthlyPoints << " points\n\n";
        }
    }
};

int main() {
    TaskPlanner planner;

    // Add all tasks
    planner.addTask(Task("Cooking", "1/day", "Cooking and related activities", 2));
    planner.addTask(Task("Buying", "2/week", "Grocery shopping", 2));
    planner.addTask(Task("CarCleaning", "1/month", "Complete car cleaning", 5));
    planner.addTask(Task("WorkAroundHouse", "1/week", "House maintenance", 5));
    planner.addTask(Task("WorkAroundGarden", "1/week", "Garden maintenance", 5));
    planner.addTask(Task("DustAndSpiderWebs", "2/week", "Dusting and cleaning", 2));
    planner.addTask(Task("Dog", "1/day", "Walking the dog", 1));
    planner.addTask(Task("Ironing", "1/week", "Ironing clothes", 5));
    planner.addTask(Task("ClothPacking", "1/week", "Organizing laundry", 3));
    planner.addTask(Task("WashingWear", "1/day", "Doing laundry", 3));
    planner.addTask(Task("BathCleaning", "1/week", "Cleaning bathroom", 3));
    planner.addTask(Task("FloorCleaning", "1/week", "Mopping floors", 3));
    planner.addTask(Task("AirCleaning", "2/week", "Vacuuming", 3));
    planner.addTask(Task("WashingEatingTools", "1/day", "Doing dishes", 1));
    planner.addTask(Task("CleaningThings", "1/day", "General tidying", 3));
    planner.addTask(Task("SortingBureaucracy", "1/week", "Organizing paperwork", 3));

    int startDay;
    std::cout << "Enter the starting day of the month (1-7, where 1 is Monday): ";
    std::cin >> startDay;
    planner.setStartDay(startDay);

    planner.distributeTasks();
    planner.displayPlan();

    return 0;
}