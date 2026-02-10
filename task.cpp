#include "task.h"
#include <fstream>
#include <sstream>


std::vector<Task> loadTasks(const std::string& filename){
  std::vector<Task> tasks;
  std::ifstream in(filename);
  std::string line;
  int counter =1;

  while(std::getline(in,line)){
    Task t;
    t.id = counter;
    t.status = line.substr(0,3);
    t.description = line.substr(4);
    tasks.push_back(t);
    counter++;

  }
  in.close();
  return tasks;

}


void saveTasks(const std::string& filename, const std::vector<Task>& tasks){
  std::ofstream out(filename);
  for(const auto& t: tasks){
    out<< t.status << " "<< t.description << "\n";

  }
  out.close();


}
