#include <stdio.h>
#include <stdlib.h>


// Sources
// http://www.6502.org/users/obelisk/
// http://www.6502.org/users/obelisk/electronics/sb-6502.html
// https://www.c64-wiki.com/wiki/Main_Page


 using Byte = unsigned char; //8 Bits
using Word = unsigned short; // 4 Bytes or 32 Bits


using u32 = unsigned int;  // Unsigned 32 Bit Integer

struct Memory{  // Memory Data Stuture
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Init(){
        for(u32 i = 0; i <MAX_MEM;i++){
            Data[i] = 0;
        }
    }

    // Fetch 1 Byte from memory
    Byte operator[](u32 adress) const{
        return Data[adress];
    }

    // Write 1 Byte to memory
    Byte& operator[](u32 adress) {

        return Data[adress];
    }
};

struct CPU {    // CPU Datastructure
   

    Word PC;    // program Counter
    Word SP;    // Stack Counter

    Byte A,X,Y; //Registers

    Byte C : 1; // Carry Flag
    Byte Z : 1; // Zero Flag
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal Mode
    Byte B : 1; // Break Mode
    Byte V : 1; // Overflow Flag
    Byte N : 1; // Negative Flag


    // Operations with OpCodes;
    static constexpr Byte INS_LDA_IM = 0xA9;    // Load Assembler Immidiate
    
     
    void  Reset(Memory& mem) {
        // Resets Program Counter, Stack Pointer,Flags,Registers,and Memory
        // Simulates this process https://www.c64-wiki.com/wiki/Reset_(Process)
        PC = 0xFFFC;
        SP  = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        mem.Init();
    }

    Byte FetchByte(u32& cycles,Memory& mem){
        Byte recieved_data = mem[PC];
        PC++;
        cycles --;
        return recieved_data;
    }

    void Execute(u32 cycles, Memory& mem){

        while(cycles > 0){
            Byte instruction = FetchByte(cycles,mem);
            switch (instruction)
            {
            case INS_LDA_IM:{
                Byte value = FetchByte( cycles,mem);
                A = value;
                if(A == 0){
                    Z = 0;
                }
                if(A & 0b10000000 > 0){
                    N = 1;
                }

                } break;
            }
        }
    }
};


int main(){
    Memory mem;
    CPU cpu;
    cpu.Reset(mem);
    // test start for LDA Im
    mem[0XFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x42;
    // end of test
    cpu.Execute(2,mem);
    return 0;
}