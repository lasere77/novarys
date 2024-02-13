#include "../include/Prog.hpp"
#include <fstream>

std::array<std::string, SizeProg> prog;


void readProgFromFile(char *argv[]) {
    std::ifstream file;
    file.open(argv[1]);
    std::string s;
    
    std::cout << "the program is loaded from: " << argv[1] << std::endl;
    
    if(file.is_open()) {
        for (int i = 0; file.peek() != EOF && i != prog.size(); i++) {
            file >> s;
            //remove binary error
            for (char c : s) {
                if (c != '0' && c != '1' || s.size() != 8) {
                    s = "00000000";
                }
            }
            prog[i] = s;
            //std::cout << s << " i: " << i << std::endl;
        }
    }
    file.close();
}

std::array<std::string, SizeProg> getProg(char *argv[]) {
    readProgFromFile(argv);
    return prog;
}