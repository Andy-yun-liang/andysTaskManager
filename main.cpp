#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include "task.h"

void printUsage() {
    std::cerr << "Usage: andysTaskManager <command> [args]\n\n"
              << "Commands:\n"
              << "  add \"description\"     Add a new task\n"
              << "  ls                     List pending tasks\n"
              << "  ls -a                  List all tasks including completed\n"
              << "  done <id>              Mark a task as complete\n"
              << "  edit <id> \"new text\"   Edit a task description\n"
              << "  del <id>               Delete a task\n";
}

int main(int argc, char** argv) {

        if(argc < 2){
            printUsage();
            return 1;
        }

        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME not set\n";
            return 1;
        }

        std::string home = home_c;
        std::string dir = home + "/.andysTaskManager";
        std::string filename = dir + "/notes.txt";

        mkdir(dir.c_str(), 0777);
        std::string cmd_used = argv[1];

        if (cmd_used == "add"){

                if(argc < 3){
                  std::cerr<<"Usage: andysTaskManager add <description>"<<"\n";
                  return 1;
                }
                std::vector<Task> tasks = loadTasks(filename);
                Task t;
                t.id = tasks.size() + 1;
                t.status = "[P]";
                t.description = argv[2];
                t.date_added = getCurrentDate();
                t.date_completed = "";
                tasks.push_back(t);
                saveTasks(filename,tasks);
                std::cout << "added: " << argv[2]<< "\n";

        }else if(cmd_used == "del"){

                if(argc < 3){
                  std::cerr<<"Usage: andysTaskManager del <id>"<<"\n";
                  return 1;
                }

                int id_num_to_be_deleted = std::stoi(argv[2]);
                std::vector<Task> tasks = loadTasks(filename);

                if (id_num_to_be_deleted < 1 || id_num_to_be_deleted > (int)tasks.size()) {
                    std::cerr << "Error: no note at line " << id_num_to_be_deleted << "\n";
                    return 1;
                }
                tasks.erase(tasks.begin() + (id_num_to_be_deleted -1));
                saveTasks(filename, tasks);
                std::cout << "deleted task [" << id_num_to_be_deleted << "]\n";

        }else if(cmd_used == "edit"){

                if(argc < 4){
                  std::cerr<<"Usage: andysTaskManager edit <id> <new text>"<<"\n";
                  return 1;
                }
                int id_of_note_to_be_edited = std::stoi(argv[2]);
                std::vector<Task> tasks = loadTasks(filename);

                if (id_of_note_to_be_edited < 1 || id_of_note_to_be_edited >= (int)tasks.size()){
                          std::cerr << "Error: no note at line " << id_of_note_to_be_edited << "\n";
                          return 1;
                }

               tasks[id_of_note_to_be_edited - 1].description = argv[3];
               saveTasks(filename,tasks);
               std::cout << "edited task [" << id_of_note_to_be_edited << "]\n";

        }else if(cmd_used == "ls"){

                bool show_all_notes = (argc > 2 && (std::string(argv[2]) == "-a" || std::string(argv[2])== "-all"));
                std::vector<Task> tasks = loadTasks(filename);

                std::cout<< std::left
                         << std::setw(10) << "ID"
                         << std::setw(10) << "STATUS"
                         << std::setw(15) << "DATE ADDED";
                if(show_all_notes){
                  std::cout << std::setw(18) << "DATE COMPLETED";
                }
                std::cout<< "DESCRIPTION" << "\n";

                std::cout<< std::string(show_all_notes ? 80: 60,'-') << "\n";

                for(const auto& t : tasks){
                            if(!show_all_notes && t.status == "[C]"){
                                continue;
                            }
                            std::string id = "[" + std::to_string(t.id) + "]";
                            std::cout << std::left
                                      << std::setw(10) << id
                                      << std::setw(10) << t.status
                                      << std::setw(15) << t.date_added;
                            if(show_all_notes){
                              std::cout<<std::setw(18) <<t.date_completed;
                            }
                            std::cout<<t.description<< "\n";
                        }

        }else if(cmd_used == "done"){

                if(argc <3){
                  std::cerr<<"Usage: andysTaskManager done <id>"<<"\n";
                  return 1;
                }

                int id_of_note_completed = std::stoi(argv[2]);
                std::vector<Task> tasks = loadTasks(filename);

                if (id_of_note_completed < 1 || id_of_note_completed > (int)tasks.size()){
                  std::cerr<<"Error: No note on line "<<id_of_note_completed<<"\n";
                  return 1;
                }
                if(tasks[id_of_note_completed - 1].status == "[P]"){
                  tasks[id_of_note_completed - 1].status = "[C]";
                  tasks[id_of_note_completed - 1].date_completed = getCurrentDate();
                }else{
                  std::cout<< "Task [" << id_of_note_completed << "] is already completed \n";
                  return 0;
                }
                saveTasks(filename, tasks);
                std::cout<<"marked note ["<<id_of_note_completed <<"] as done"<<"\n";

        }else{
            std::cerr << "Unknown command: \"" << cmd_used << "\"\n\n";
            printUsage();
            return 1;
        }
}
