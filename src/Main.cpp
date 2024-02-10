#include <iostream>
#include <cstdint>
#include "../include/Prog.hpp"

using UByte = uint8_t;

union Byte {
    int8_t SByte;
    uint8_t UByte;
};

const bool signedNb = true;

//this variable is used to hide the moment when there is a conditional jump and the info has not changed, because no action has been taken.
bool displayInfo = true; 

struct Memory {

    std::array<std::string, SizeProg> prog;
    int decProg[255];

    void init() {
        prog = getProg(); //prog
        //replace all unused space by "00000000"
        for(int i = 0; i != prog.size(); i++) {
            if(prog.at(i).empty()) {
                prog.at(i) = "00000000";
            }
        }
        decodeProg(); //set same prog but in decimal
    }
    void decodeProg() {
        for(int i = 0; i != SizeProg; i++) {
            if(!prog[i].empty()) {
                decProg[i] = std::stoi(prog[i], nullptr, 2);
                if(signedNb && prog[i].at(0) == '1') {
                    decProg[i] = decProg[i] * -1;
                }
                //std::cout << "decoded prog: " << decProg[i] << std::endl;
            }
        }
    }

    int getMode(uint8_t tick) {
        int computerMode = 0;
        if(prog[tick].at(0) == '1') {
            computerMode+=128;
        }
        if(prog[tick].at(1) == '1') {
            computerMode+=64;
        }
        return computerMode;
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


    int getConditionId(uint8_t tick) {
        int conditonID = 0;
        if(prog[tick].at(5) == '1') {
            conditonID+=4;
        }
        if(prog[tick].at(6) == '1') {
            conditonID+=2;
        }
        if(prog[tick].at(7) == '1') {
            conditonID++;
        }
        std::cout << "conditonID: " << conditonID << std::endl;
        return conditonID;
    } 

    int getAluId(uint8_t tick) {
        int getAluId = 0;
        if(prog[tick].at(5) == '1') {
            getAluId+=4;
        }
        if(prog[tick].at(6) == '1') {
            getAluId+=2;
        }
        if(prog[tick].at(7) == '1') {
            getAluId++;
        }
        return getAluId;
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
    Byte IN; // input of compuiter ID=6
    Byte OUT; //output of computer ID=6

    void init() {
        A.SByte = C.SByte = D.SByte = R.SByte = F.SByte = X.SByte = 0;
        A.UByte = C.UByte = D.UByte = R.UByte = F.UByte = X.UByte = 0;
        static_cast<uint>(NV = 0);

        OUT.SByte = OUT.SByte = 0;
        IN.UByte = IN.UByte = 0;
    }

    void resetOutput() {
        OUT.SByte = OUT.UByte = 0;
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

    void alu(uint mode) {
        switch (mode) {
        case 0: // OR
            std::cout << "or" << std::endl;
            R.SByte = (C.SByte | D.SByte);
            R.UByte = (C.UByte | D.UByte); 
            break;
        case 1: // NAND
            std::cout << "nand" << std::endl;
            R.SByte = ~(C.SByte & D.SByte);
            R.UByte = ~(C.UByte & D.UByte); 
            break;
        case 2: // NOR
            std::cout << "nor" << std::endl;
            R.SByte = ~(C.SByte | D.SByte);
            R.UByte = ~(C.UByte | D.UByte); 
            break;
        case 3: // AND
            std::cout << "and" << std::endl;
            R.SByte = (C.SByte & D.SByte);
            R.UByte = (C.UByte & D.UByte); 
            break;
        case 4: // ADD
            std::cout << "add" << std::endl;
            R.SByte = C.SByte + D.SByte;
            R.UByte = C.UByte + D.UByte;
            break;
        case 5: // SUB
            std::cout << "sub" << std::endl;
            R.SByte = C.SByte - D.SByte;
            R.UByte = C.UByte - D.UByte;
            break;
        default:
            std::cout << "hmmm that shouldn't have happened.../{alu}}" << std::endl;
            break;
        }
    }

    bool condition(int condition, int nb) {
        switch (condition) {
        case 0: //never
            return false;
            break;
        case 1: // nb = 0
            if(nb == 0)
                return true;
        case 2: // nb < 0
            if(nb < 0)
                return true;
            break;
        case 3: // <=0
            if(nb <= 0)
                return true;
            break;
        case 4: // always
            return true;
            break;
        case 5: // !=0
            if(nb != 0)
                return true;
            break;
        case 6: // >=0
            if(nb >= 0)
                return true;
            break;
        case 7: // >0
            if(nb > 0)
                return true;
            break;
        default:
            std::cout << "hmmm that shouldn't have happened.../{condition}" << std::endl;
            break;
        }
        std::cout << "No" << std::endl;
        return false;
    }

    void conditionnalJump() {
        std::cout << "Yes" << std::endl;
        NV = A.UByte - 1; //A.UByte - 1 to execute A.UByte on the while loop
        displayInfo = false;
    }

    void immediate(uint8_t nb) {
        A.UByte = A.SByte = nb;
    }

    void copy(Byte &enter, Byte &exit) {
        exit = enter;
    }


    void info() {
        //This condition solves the A.UByte -1 problem caused by the conditionnalJump function.
        if(displayInfo) {
            std::cout << "tick: "<< static_cast<uint>(NV) << std::endl;
            std::cout << "----" << std::endl;
            if (signedNb) {
                std::cout << "IN: " << static_cast<int>(IN.SByte) << std::endl;
                std::cout << "reg A: " << static_cast<int>(A.SByte) << std::endl;
                std::cout << "reg C: " << static_cast<int>(C.SByte) << std::endl;
                std::cout << "reg D: " << static_cast<int>(D.SByte) << std::endl;
                std::cout << "reg R: " << static_cast<int>(R.SByte) << std::endl;
                std::cout << "reg F: " << static_cast<int>(F.SByte) << std::endl;
                std::cout << "reg X: " << static_cast<int>(X.SByte) << std::endl;
                std::cout << "OUT: " << static_cast<int>(OUT.SByte) << std::endl;
            }else {
                std::cout << "IN: " << static_cast<uint>(IN.UByte) << std::endl;
                std::cout << "reg A: " << static_cast<uint>(A.UByte) << std::endl;
                std::cout << "reg C: " << static_cast<uint>(C.UByte) << std::endl;
                std::cout << "reg D: " << static_cast<uint>(D.UByte) << std::endl;
                std::cout << "reg R: " << static_cast<uint>(R.UByte) << std::endl;
                std::cout << "reg F: " << static_cast<uint>(F.UByte) << std::endl;
                std::cout << "reg X: " << static_cast<uint>(X.UByte) << std::endl;
                std::cout << "OUT: " << static_cast<uint>(OUT.UByte) << std::endl;   
            }
            std::cout << "----" << std::endl;
        }
        displayInfo = true;
    }

    void incNV() {
        static_cast<uint>(NV++);
    }
};

/*
*"BUG" = 
*/
int main() {
    std::cout << "launch the computer..." << std::endl;
    
    cpu cpu;
    Memory mem;

    cpu.init();
    mem.init();

    while (static_cast<uint>(cpu.NV) < mem.prog.size()) {
        std::cout << std::endl; 
        switch (mem.getMode(static_cast<uint>(cpu.NV))) {
        case 0:
            std::cout << "immediate" << std::endl;
            cpu.immediate(mem.decProg[static_cast<uint>(cpu.NV)]);
            break;
        case 64:
            std::cout << "alu" << std::endl;
            cpu.alu(mem.getAluId(static_cast<uint>(cpu.NV)));
            break;
        case 128:
            std::cout << "copy" << std::endl;
            cpu.copy(cpu.getRegisterById(mem.getRegIdInputCopy(static_cast<uint>(cpu.NV)), false), cpu.getRegisterById(mem.getRegIdOutputCopy(static_cast<uint>(cpu.NV)), true));
            break;
        case 192:
            std::cout << "condition" << std::endl;
            if(cpu.condition(mem.getConditionId(static_cast<uint>(cpu.NV)), cpu.R.SByte))
                cpu.conditionnalJump();
            break;
        default:
            std::cout << "hmmm that shouldn't have happened.../{main}" << std::endl;
            break;
        }
        cpu.info();
        cpu.incNV();
        cpu.resetOutput();
    }
    return 0;
}