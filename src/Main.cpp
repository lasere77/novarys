#include <iostream>
#include "../include/Prog.hpp"

using Byte = unsigned char;
using ByteWord = unsigned short;

struct cpu {

    Byte NV; //(instruction pointer register) 

    Byte A; //regiter for instante nomber (register 0)
    Byte C; //regiter1 for aul (register 1)
    Byte D; //regiter2 for aul (register 2)
    Byte R; //regiter for aul resulte op aul (register 3)
    Byte F; //regiter (register 4)
    Byte X; //regiter (register 5)

    void init() {
        A = C = D = R = F = X = 0;
        NV = 0;
    }

    Byte getNV() {
        NV++;
        return NV - 1;
    }

};


int main() {
    std::cout << "test of emulat novarys" << std::endl;
    
    cpu cpu;
    cpu.init();
    decodeProg();
    
    while (true) {

    }
    
    return 0;
}