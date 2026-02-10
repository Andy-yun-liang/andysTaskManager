#include "task.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>

std::string getCurrentDate(){
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&time);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", tm);
    return std::string(buf);
}

std::vector<Task> loadTasks(const std::string& filename){
    std::vector<Task> tasks;
    std::ifstream in(filename);
    std::string line;
    int counter = 1;

    while(std::getline(in, line)){
        Task t;
        t.id = counter;

        // split by | delimiter
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, t.status, '|');
        std::getline(ss, t.description, '|');
        std::getline(ss, t.date_added, '|');
        std::getline(ss, t.date_completed, '|');

        tasks.push_back(t);
        counter++;
    }
    in.close();
    return tasks;
}

void saveTasks(const std::string& filename, const std::vector<Task>& tasks){
    std::ofstream out(filename);
    for(const auto& t : tasks){
        out << t.status << "|"
            << t.description << "|"
            << t.date_added << "|"
            << t.date_completed << "\n";
    }
    out.close();
}
