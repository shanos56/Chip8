#ifndef CPUSTATE_H
#define CPUSTATE_H

#include "definitions.h"
#include "address.h"
#include <vector>
#include "byteregister.h"


class CpuState {

public:
    // 16 8-bit registers
    std::vector<ByteRegister> v = std::vector<ByteRegister>(16);

    // Program counter. Stores the currently executing address.
    // set program counter to 0x200, the beginning of roms
    Address pc = Address(PROGRAM_BEGINNING);

     // Stores memory addresses. Set this to 0 since we aren't storing anything at initialization.
    WordRegister i = WordRegister();

    // Timers
    ByteRegister delayTimer = ByteRegister(0);
    ByteRegister soundTimer = ByteRegister(0);

    // Some instructions require pausing, such as Fx0A.
    bool paused = false;

    // Don't initialize this with a size in order to avoid empty results.
    std::vector<u16> stack = std::vector<u16>(16); // the stack has a limit of 16 16 bit storages




};
#endif // CPUSTATE_H
