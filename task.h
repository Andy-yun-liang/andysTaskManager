#pragma once
#include <string>
#include <vector>

struct Task{
  int id;
  std::string status;
  std::string description;


};


std::vector<Task> loadTasks(const std::string& filename);
void saveTasks(const std::string& filename, const std::vector<Task>& tasks);


