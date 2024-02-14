# Novarys
very simple PC emulator

---
## Novarys information
This program is a computer emulator but not a regular computer.
in fact this program will emulate the PC that you create in the game "Turing complete"
and it has the architecture: OVERTURE

## Credits

made by lasere77 


## compile
**the sources are compiled :**
with gnu g++, you can use the Makefile
it work on linux and windows

---
## how to program it?

### instruction

If the two highest bits are disabled, you are in immediate value mode (stores the value in register A)
but this value can go from 0 to 63 by enabling/disabling the other bits.

<img src="README IMG/immediate_value.png">

If only the second bit of the most important bits (the penultimate bit) is set.
Then you are in calculation mode C and D are the two arguments to the operations and R is the result of this operation.
for exemple: (01000101) = (C - D) -> R
The first 3 bits define the operation to be performed.

> 000 = OR; 001 = NAND; 010 = NOR; 011 = AND; 100 = ADD; 101 = SUB

<img src="README IMG/calculation.png">


If only the first bit of the most important bits (the last) is set, then you are in copy mode.
The first 3 bits define which register the value will be sent to and bits 4, 5 and 6 define which register will be copied.
To select input or output, you need to set the last two bits of the input or output section.

<img src="README IMG/copy.png">


If the two most important bits (the last two bits) are set, then you are in condition mode.
The first 3 bits define the conditions to be performed

> 000 -> NERVER; 001 -> =0; 010 -> <0; 011 -> <=0; 100 -> ALWAYS; 101 -> != 0; 110 -> >=0; 111 -> >0

<img src="README IMG/condition.png">


### How to write/load the program in Novarys?  
Simply write the program in a text file and pass the file path as an argument to Novarys (./novarys.exe filePath). 
Please note that each instruction in the program must be separated by a space, a tab or a line feed. Please see the example (binary.nova).

---
## precision
you will find in the Main.cpp file a signedNb variable if it is set to true then the numbers will be displayed as signed numbers and vice versa,
but it is important to note that even if this variable is set to false the numbers will still be treated as signed so if a number is > = 128
(unsigned signedNb = false) it will be counted as negative in the condition mode.
furthermore, if an addition is performed and the result is greater than or equal to 128, 
then the number will become a negative number corresponding to the binary of the result (only if signedNb = true)
and if you perform a subtraction and the result is negative, but (signedNb = false),
then the result will be the positive binary corresponding to the initial result.

#### Binary register names

to activate register A we set the value of the three bits to 0  
C to 1  
D to 2  
R to 3  
F to 4  
X to 5  