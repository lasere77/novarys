#include "../include/Prog.hpp"
#include <bitset>

std::array<std::string, SizeProg> prog = {"10000001"};
int decProg[255];

void decodeProg() {
    for(int i = 0; i != SizeProg; i++) {
        if(!prog[i].empty()) {
            decProg[i] = std::stoi(prog[i], nullptr, 2);
            //std::cout << decProg[i] << std::endl;
        }
    }
}

std::array<std::string, SizeProg> getProg() {
    return prog;
}