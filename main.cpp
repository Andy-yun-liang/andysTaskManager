#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char** argv) {
        

        if(argc <2){

        std::cerr<< "Usage: andysTaskManager add \"description\"" << "\n";

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

        // create ~/.andy if it doesn't exist (ok if it already exists)
        mkdir(dir.c_str(), 0777);


        std::string cmd_used = argv[1];

        if (cmd_used == "add"){
        
                if(argc < 3){

                std::cerr<<"Usage: andysTaskManager add <description>"<<"\n";
                return 1;
                }
                std::ofstream file(filename, std::ios::app);
                file <<"[ ] "<< argv[2]<<"\n";
                file.close();
                std::cout << "added: " << argv[2]<< " into notes.txt\n";
        
        }else if(cmd_used == "del"){
                
                if(argc < 3){

                        std::cerr<<"Usage: andysTaskManager del <id>"<<"\n";
                        return 1;
                }

                int id_num_to_be_deleted = std::stoi(argv[2]); //string to integer
                std::ifstream in(filename);
                if (!in) {
                    std::cerr << "Error: notes.txt can't be opened\n";
                    return 1;
                }

                std::vector<std::string> kept;
                std::string line;
                int counter = 1;

                while (std::getline(in, line)) {
                    if (counter != id_num_to_be_deleted) {
                        kept.push_back(line);
                    }
                    counter++;
                }
                in.close();

                if (id_num_to_be_deleted < 1 || id_num_to_be_deleted >= counter) {
                    std::cerr << "Error: no note at line " << id_num_to_be_deleted << "\n";
                    return 1;
                }

                std::ofstream out(filename); // overwrite
                for (const auto& s : kept) {
                    out << s << "\n";
                }
                out.close();

                std::cout << "deleted note [" << id_num_to_be_deleted << "]\n";



          
        }else if(cmd_used == "edit"){

                if(argc < 4){

                        std::cerr<<"Usage: andysTaskManager edit <id> <new text>"<<"\n";
                        return 1;
                }

                
                int id_of_note_to_be_edited = std::stoi(argv[2]);
                std::string new_text = argv[3];
                        
                std::ifstream in(filename);
                if(!in){
                        std::cerr<<"Error: notes.txt can't be opened"<<"\n";
                        return 1;
                }


                std::vector<std::string> new_file;
                std::string line;
                int counter = 1;

                while (std::getline(in,line)){
                
                        if(counter == id_of_note_to_be_edited){
                                std::string status = line.substr(0,4);
                                new_file.push_back(status + new_text);
                        }else{
                                new_file.push_back(line);
                        }

                        counter++;
                }
                in.close();

                if (id_of_note_to_be_edited < 1 || id_of_note_to_be_edited >= counter){
                        
                          std::cerr << "Error: no note at line " << id_of_note_to_be_edited << "\n";
                          return 1;
                }


               std::ofstream out(filename); // overwrite
               for (const auto& s : new_file) {
                   out << s << "\n";
               }
               out.close();

               std::cout << "edited note [" << id_of_note_to_be_edited << "]\n";


        }else if(cmd_used == "ls"){
                

                bool show_all_notes = (argc > 2 && (std::string(argv[2]) == "-a" || std::string(argv[2])== "-all"));



                std::ifstream file(filename);
                std::string line;
                int counter = 1;
                

                //column name and header section
                std::cout<< std::left
                         << std::setw(10) << "TASK ID"
                         << std::setw(10) << "STATUS"
                         << "TASK" << "\n";

                std::cout<< std::string(40, '-') << "\n";
                

                while (std::getline(file,line)){

                        if (!show_all_notes && line.substr(0,3) =="[x]"){

                            counter++;
                            continue;
                        }
                        std::string id = "[" + std::to_string(counter) + "]";
                        std::cout << std::left
                                      << std::setw(10) <<id
                                      << std::setw(10) << line.substr(0, 3)
                                      << line.substr(4)
                                      << "\n";
                        counter++;
                }
                file.close();
        }else if(cmd_used == "done"){

                if(argc <3){
                  std::cerr<<"Usage: andysTaskManager done <id>"<<"\n";
                  return 1;
                }

                int id_of_note_completed = std::stoi(argv[2]);

                std::ifstream in(filename);
                if(!in){

                  std::cerr<<"Error: notes.txt can't be opened"<<"\n";
                  return 1;
                }
                std::string line;
                std::vector<std::string> new_file;

                int counter = 1;

                while(std::getline(in,line)){
                  if(counter == id_of_note_completed){
                    if(line.substr(0,3) == "[ ]"){
                      line[1] = 'x';
                    }
                  }
                  new_file.push_back(line);
                  counter++;
                }
                in.close();

                if (id_of_note_completed < 1 || id_of_note_completed >= counter){
                  std::cerr<<"Error: No note on line "<<id_of_note_completed<<"\n";
                  return 1;
                }

                std::ofstream out(filename);
                for( const auto& s: new_file){
                  out<< s<< "\n";
                }
                out.close();

                std::cout<<"marked note ["<<id_of_note_completed <<"] as done"<<"\n";



        }else{

                std::cout<< "command not found"<< "\n";
        }




}
