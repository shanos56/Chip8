#include "oppinstructions.h"
#include "bitwise.h"

OppInstructions::OppInstructions(Memory &mem,FrameBuffer &buffer, CpuState &state, Input &input):pc(state.pc),memory(mem),buffer(buffer),stack(state.stack),v(state.v),i(state.i),input(input), state(state)
{


}


u16 OppInstructions::get_nnn (const RegisterPair &oppcode) const {
    return static_cast<u16>((bitwise::low_nibble(oppcode.high()) << 8) | oppcode.low());
}

u8 OppInstructions::get_n (const RegisterPair &oppcode) const {
    return bitwise::low_nibble(oppcode.low());
}

u8 OppInstructions::get_kk (const RegisterPair &pair) const {
    return pair.low();
}
u8 OppInstructions::get_x (const RegisterPair &pair) const {
    // x is the bottom four bits of the higher byte
    return bitwise::low_nibble(pair.high());

}
u8 OppInstructions::get_y (const RegisterPair &pair) const {
    // y is top four bits of the lower byte
    return bitwise::high_nibble(pair.low());
}

void OppInstructions::oppcode_00E0() { // clears the display
    buffer.reset();
}
void OppInstructions::oppcoe_00EE() { // gets last address from stack
    pc = stack.back();
    stack.pop_back();
}

void OppInstructions::oppcode_1nnn (const RegisterPair &oppcode) { // program counter set to nnn
    pc = get_nnn(oppcode);
}

void OppInstructions::oppcode_2nnn(const RegisterPair &oppcode){ // puts current pc address on stack and pc = nnn
    stack.push_back(oppcode.value());
    oppcode_1nnn(oppcode);
}

void OppInstructions::oppcode_3xkk (const RegisterPair &oppcode){ // if value in register v[x] == kk then skip the next instruction
    if (v[get_x(oppcode)] == get_kk(oppcode)) {
        pc = pc + 2;
    }
}


void OppInstructions::oppcode_4xkk(const RegisterPair &oppcode) { // The interpreter compares register V[x] to kk, and if they are not equal, increments the program counter by 2.
    if (!(v[get_x(oppcode)] == get_kk(oppcode))) {
        pc = pc + 2;
    }

}
void OppInstructions::oppcode_5xy0(const RegisterPair &oppcode) { // The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
    if (v[get_x(oppcode)] == v[get_y(oppcode)]) {
        pc = pc + 2;
    }
}
void OppInstructions::oppcode_6xkk(const RegisterPair &oppcode) { // The interpreter puts the value kk into register Vx.
    u8 x = get_x(oppcode);

    v[x].set(get_kk(oppcode));

}
void OppInstructions::oppcode_7xkk(const RegisterPair &oppcode) { // Adds the value kk to the value of register Vx, then stores the result in Vx.
    v[get_x(oppcode)] += get_kk(oppcode);
}
void OppInstructions::oppcode_8xy0(const RegisterPair &oppcode) { // Stores the value of register Vy in register Vx.
    v[get_x(oppcode)] = v[get_y(oppcode)];
}
void OppInstructions::oppcode_8xy1(const RegisterPair &oppcode){ // Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
    u8 x = get_x(oppcode);

    v[x] = ByteRegister(v[x].value() | v[get_y(oppcode)].value());
}


void OppInstructions::oppcode_8xy2(const RegisterPair &oppcode) { // Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
     u8 x = get_x(oppcode);
     v[x] = ByteRegister(v[x].value() & v[get_y(oppcode)].value());
}
void OppInstructions::oppcode_8xy3(const RegisterPair &oppcode) { // Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
    u8 x = get_x(oppcode);
         v[x] = ByteRegister(v[x].value() ^ v[get_y(oppcode)].value());

}
void OppInstructions::oppcode_8xy4(const RegisterPair &oppcode) { // The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
    u8 x = get_x(oppcode);
    WordRegister result = WordRegister();
    result.set(v[x].value() + v[get_y(oppcode)].value());

    v[0xf] = (result.value() & 0x100) >> 8;

    v[x] = result.low();

}
void OppInstructions::oppcode_8xy5(const RegisterPair &oppcode) { // If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
    u8 x = get_x(oppcode), y = get_y(oppcode);

    v[0xf] = static_cast<u8>(v[x].value() > v[y].value());

    v[x] = v[x].value() - v[y].value();

}
void OppInstructions::oppcode_8xy6(const RegisterPair &oppcode){ // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
    u8 x = get_x(oppcode);
    v[0xf] = v[get_x(oppcode)].value() & 0x01;

    v[x] = v[x].value() >> 1;
}
void OppInstructions::oppcode_8xy7(const RegisterPair &oppcode){ // If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
    u8 x = get_x(oppcode), y = get_y(oppcode);

    v[0xf] = static_cast<u8>(v[y].value() > v[x].value());

    v[x] = v[y].value() - v[x].value();

}
void OppInstructions::oppcode_8xyE(const RegisterPair &oppcode) { // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.

    u8 x = get_x(oppcode);
    v[0xf] = (v[get_x(oppcode)].value() & 0x80) >> 7;

    v[x] = static_cast<u8>(v[x].value() << 1);

}

void OppInstructions::oppcode_9xy0(const RegisterPair &oppcode){ // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
    u8 x = get_x(oppcode), y = get_y(oppcode);

    if (v[x] != v[y]) {
        pc = pc + 2;
    }


}
void OppInstructions::oppcode_Annn(const RegisterPair &oppcode) { // The value of register I is set to nnn.

    i.set(get_nnn(oppcode));

}
void OppInstructions::oppcode_Bnnn(const RegisterPair &oppcode){ // The program counter is set to nnn plus the value of V0.
    pc = get_nnn(oppcode) + v[0x0].value();
}

void OppInstructions::oppcode_Cxkk(const RegisterPair &oppcode) { // The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
     v[get_x(oppcode)] = static_cast<u8>(rand() % 256) & get_kk(oppcode);

}
void OppInstructions::oppcode_Dxyn(const RegisterPair &oppcode) { // The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
    u8 x = get_x(oppcode), y = get_y(oppcode), height = get_n(oppcode);
    u8 width = 8;


   for (int row = 0; row < height; row++){
       u8 mem = memory.read(static_cast<u16>(i.value() + row));

       for (int col = 0; col < width; col++) {
           if ((mem & 0x80) > 0) {
                buffer.set_pixel(v[x].value()+col,v[y].value() + row);
           }

           mem <<= 1;
       }
   }

}
void OppInstructions::oppcode_Ex9E(const RegisterPair &oppcode) { // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
    if (input.is_pressed(v[get_x(oppcode)].value())){
        pc =  pc + 2;
    }

}
void OppInstructions::oppcode_ExA1(const RegisterPair &oppcode) { // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
    if (!input.is_pressed(v[get_x(oppcode)].value())){
        pc = pc + 2;
    }
}
void OppInstructions::oppcode_Fx07(const RegisterPair &oppcode) { // The value of DT is placed into Vx.
    v[get_x(oppcode)] = state.delayTimer;
}
void OppInstructions::oppcode_Fx0A(const RegisterPair &oppcode) { // All execution stops until a key is pressed, then the value of that key is stored in Vx.
    u8 x = get_x(oppcode);
    this->state.paused = true;
    bool &paused = state.paused;
    auto &_v = v;

   input.onNextKeyPress([paused, _v, x](CButton button) mutable->void {
        paused = false;
        _v[x] = static_cast<u8>(button);
    });
}
void OppInstructions::oppcode_Fx15(const RegisterPair &oppcode){ // DT is set equal to the value of Vx.

    state.delayTimer = v[get_x(oppcode)];
}
void OppInstructions::oppcode_Fx18(const RegisterPair &oppcode) {// ST is set equal to the value of Vx.
    state.soundTimer = v[get_x(oppcode)];
}
void OppInstructions::oppcode_Fx1E(const RegisterPair &oppcode){ // The values of I and Vx are added, and the results are stored in I.
    state.i.set(v[get_x(oppcode)].value() + state.i.value());
}
void OppInstructions::oppcode_Fx29(const RegisterPair &oppcode){ // The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.

    state.i.set(v[get_x(oppcode)].value());
}
void OppInstructions::oppcode_Fx33(const RegisterPair &oppcode){ // The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
    u8 _v = v[get_x(oppcode)].value();
    WordRegister _i = i;
    memory.write(_i, static_cast<u8>(_v / 100));
    _i.increment();
    memory.write(_i, static_cast<u8>((_v % 100) / 10));
    _i.increment();
    memory.write(_i, static_cast<u8>(_v % 10));

}
void OppInstructions::oppcode_Fx55(const RegisterPair &oppcode) { // The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
    u8 x = get_x(oppcode);
    u16 _i = i.value();
    for (u16 c = 0 ;c <= x; c++) {
        memory.write(Address(_i+c),v[c].value());
    }
}
void OppInstructions::oppcode_Fx65(const RegisterPair &oppcode){ // The interpreter reads values from memory starting at location I into registers V0 through Vx.
    u8 x = get_x(oppcode);
    u16 _i = i.value();
    for (u16 c = 0 ;c <= x; c++) {
        v[c] = memory.read(Address(_i+c));
    }
}



