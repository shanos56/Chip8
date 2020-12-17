#ifndef OPPINSTRUCTIONS_H
#define OPPINSTRUCTIONS_H
#include "definitions.h"
#include "memory.h"
#include "framebuffer.h"
#include "registerpair.h"
#include "input.h"
#include "cpustate.h"

class OppInstructions
{
private:
    Address &pc;
    Memory & memory;
    FrameBuffer &buffer;
    std::vector<u16> &stack;
     std::vector<ByteRegister> &v;
     WordRegister &i;
     Input &input;

     CpuState &state;


     u8 get_kk (const RegisterPair &oppcode) const;
     u8 get_x (const RegisterPair &oppcode) const;
     u8 get_y (const RegisterPair &oppcode) const;
     u16 get_nnn (const RegisterPair &oppcode) const;
     u8 get_n (const RegisterPair &oppcode) const;

public:
    OppInstructions(Memory &mem,FrameBuffer &buffer, CpuState &state, Input &input);


    void oppcode_00E0(); // clears the display
    void oppcoe_00EE(); // gets last address from stack

    void oppcode_1nnn (const RegisterPair &oppcode); // program counter set to nnn

    void oppcode_2nnn(const RegisterPair &oppcode); // puts current pc address on stack and pc = nnn

    void oppcode_3xkk (const RegisterPair &oppcode); // The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.

    void oppcode_4xkk(const RegisterPair &oppcode); // The interpreter compares register V[x] to kk, and if they are not equal, increments the program counter by 2.

    void oppcode_5xy0(const RegisterPair &oppcode); // The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.

    void oppcode_6xkk(const RegisterPair &oppcode); // The interpreter puts the value kk into register Vx.

    void oppcode_7xkk(const RegisterPair &oppcode); // Adds the value kk to the value of register Vx, then stores the result in Vx.

    void oppcode_8xy0(const RegisterPair &oppcode); // Stores the value of register Vy in register Vx.

    void oppcode_8xy1(const RegisterPair &oppcode);// Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.

    void oppcode_8xy2(const RegisterPair &oppcode); // Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.

    void oppcode_8xy3(const RegisterPair &oppcode); // Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.

    void oppcode_8xy4(const RegisterPair &oppcode); // The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.

    void oppcode_8xy5(const RegisterPair &oppcode); // If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.

    void oppcode_8xy6(const RegisterPair &oppcode); // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.

    void oppcode_8xy7(const RegisterPair &oppcode); // If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.

    void oppcode_8xyE(const RegisterPair &oppcode); // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.

    void oppcode_9xy0(const RegisterPair &oppcode); // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.

    void oppcode_Annn(const RegisterPair &oppcode); // The value of register I is set to nnn.

    void oppcode_Bnnn(const RegisterPair &oppcode); // The program counter is set to nnn plus the value of V0.

    void oppcode_Cxkk(const RegisterPair &oppcode); // The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.

    void oppcode_Dxyn(const RegisterPair &oppcode); // The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.

    void oppcode_Ex9E(const RegisterPair &oppcode); // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.

    void oppcode_ExA1(const RegisterPair &oppcode); // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.

    void oppcode_Fx07(const RegisterPair &oppcode); // The value of DT is placed into Vx.

    void oppcode_Fx0A(const RegisterPair &oppcode); // All execution stops until a key is pressed, then the value of that key is stored in Vx.

    void oppcode_Fx15(const RegisterPair &oppcode); // DT is set equal to the value of Vx.

    void oppcode_Fx18(const RegisterPair &oppcode); // ST is set equal to the value of Vx.

    void oppcode_Fx1E(const RegisterPair &oppcode); // The values of I and Vx are added, and the results are stored in I.

    void oppcode_Fx29(const RegisterPair &oppcode); // The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.

    void oppcode_Fx33(const RegisterPair &oppcode); // The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.

    void oppcode_Fx55(const RegisterPair &oppcode); // The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.

    void oppcode_Fx65(const RegisterPair &oppcode); // The interpreter reads values from memory starting at location I into registers V0 through Vx.


};



#endif // OPPINSTRUCTIONS_H
