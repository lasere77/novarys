#include "../include/Prog.hpp"
#include <bitset>

std::string prog[SizeProg] = {"10110001", "10110001", "10110110"};
int decProg[255];

void decodeProg() {
    for(int i = 0; i != SizeProg; i++) {
        if(!prog[i].empty()) {
            decProg[i] = std::stoi(prog[i], nullptr, 2);
            std::cout << decProg[i] << std::endl;
        }
    }
}