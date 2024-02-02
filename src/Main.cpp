#include <iostream>
#include <cstdint>
#include "../include/Prog.hpp"

using UByte = uint8_t;

union Byte {
    int8_t SByte;
    uint8_t UByte;
};

bool signedNb = true;

struct Memory {

    std::array<std::string, SizeProg> prog;

    void init() {
        decodeProg();
        prog = getProg(); //prog
        //replace all unused space by "00000000"
        for(int i = 0; i != prog.size(); i++) {
            if(prog.at(i).empty()) {
                prog.at(i) = "00000000";
            }
        }
    }

    int getMode(uint8_t tick) {
        int copyMode = 0;
        if(prog[tick].at(0) == '1') {
            std::cout << "copy" << std::endl;
            copyMode+=128;
        }
        if(prog[tick].at(1) == '1') {
            copyMode+=64;
        }
        return copyMode;
    }

    int getRegIdOutputCopy(uint8_t tick) {
        int regout = 0;
        if(prog[tick].at(5) == '1') {
            regout+=4;
        }
        if(prog[tick].at(6) == '1') {
            regout+=2;
        }
        if(prog[tick].at(7) == '1') {
            regout++;
        }
        std::cout << "regout: " << regout << std::endl;
        return regout;
    }

    int getRegIdInputCopy(uint8_t tick) {
        int regin = 0;
        if(prog[tick].at(2) == '1') {
            regin+=4;
        }
        if(prog[tick].at(3) == '1') {
            regin+=2;
        }
        if(prog[tick].at(4) == '1') {
            regin++;
        }
        std::cout << "regin: " << regin << std::endl;
        return regin;
    } 
};


struct cpu {

    UByte NV; //(instruction pointer register) 

    Byte A; //regiter for instante nomber (register 0) ID=0
    Byte C; //regiter1 for aul (register 1) ID=1
    Byte D; //regiter2 for aul (register 2) ID=2
    Byte R; //regiter for aul resulte op aul (register 3) ID=3 
    Byte F; //regiter (register 4) ID=4
    Byte X; //regiter (register 5) ID=5

    //there have the same ID but is not at the same possition on binary
    Byte IN; // input of compuiter ID = 6
    Byte OUT; //output of computer ID= 6

    void init() {
        A.SByte = C.SByte = D.SByte = R.SByte = F.SByte = X.SByte = 0;
        A.UByte = C.UByte = D.UByte = R.UByte = F.UByte = X.UByte = 0;
        static_cast<uint>(NV = 0);
    }

    /*
    *set lasteBits = 1 if you try to convert getRegIdOutputCopy
    *else set lasteBits = 0 (this is if you try to convert getRegIdInputCopy)
    */
    Byte &getRegisterById(int ID, bool lasteBits) {
        switch (ID) {
        case 0:
            return A;
        case 1:        
            return C;
        case 2:
            return D;
        case 3:
            return R;
        case 4:
            return F;
        case 5:
            return X;
        }
        //input and output
        if(ID == 6 && !lasteBits) {
            return IN;
        }else if(ID == 6 && lasteBits) {
            return OUT;
        }
    }

    void copy(Byte &enter, Byte &exit) {
        exit = enter;
    }

    //for the moment the value is print as usigned. not permanent.
    void info() { 
        std::cout << "tick: "<< static_cast<uint>(NV) << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "reg A: " << static_cast<uint>(A.UByte) << std::endl;
        std::cout << "reg C: " << static_cast<uint>(C.UByte) << std::endl;
        std::cout << "reg D: " << static_cast<uint>(D.UByte) << std::endl;
        std::cout << "reg R: " << static_cast<uint>(R.UByte) << std::endl;
        std::cout << "reg F: " << static_cast<uint>(F.UByte) << std::endl;
        std::cout << "reg X: " << static_cast<uint>(X.UByte) << std::endl;
        std::cout << "----" << std::endl;
    }

    void incNV() {
        static_cast<uint>(NV++);
    }
};

int main() {
    std::cout << "test of emulat novarys" << std::endl;
    
    cpu cpu;
    Memory mem;

    cpu.init();
    mem.init();

    while (static_cast<uint>(cpu.NV) < mem.prog.size()) {
        switch (mem.getMode(static_cast<uint>(cpu.NV))) {
        case 0:
            //immediate();
            break;
        case 64:
            //alu();
            break;
        case 128:
            cpu.copy(cpu.getRegisterById(mem.getRegIdInputCopy(static_cast<uint>(cpu.NV)), false), cpu.getRegisterById(mem.getRegIdOutputCopy(static_cast<uint>(cpu.NV)), true));
            break;
        case 192:
            //condition();
            break;
        default:
            std::cout << "hmmm that shouldn't have happened..." << std::endl;
            break;
        } 
        cpu.info();
        cpu.incNV();
    }
    cpu.info();
    return 0;
}