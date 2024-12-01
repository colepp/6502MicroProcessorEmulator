#include <stdio.h>
#include <stdlib.h>

// http://www.6502.org/users/obelisk/
// http://www.6502.org/users/obelisk/electronics/sb-6502.html



struct CPU {
    using Byte = unsigned char; //8 Bits
    using Word = unsigned short; // 4 Bytes or 32 Bits

    Word PC;    // program Counter
    Word SP;    // Stack Counter

    Byte A,X,Y; //Registers

    Byte C : 1; // Carry Flag
    Byte Z : 1; // Zero Flag
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal Mode
    Byte B : 1; // Break Mode
    Byte O : 1; // Overflow Flag
    Byte N : 1; // Negative Flag
    
     

};


int main(){

    return 0;
}