#ifndef CPU_H
#define CPU_H

#include <vector>
#include "definitions.h"
#include "byteregister.h"
#include "address.h"
#include "sprites.h"
#include "memory.h"
#include "framebuffer.h"
#include "cpustate.h"
#include "oppinstructions.h"

class cpu
{
public:
    cpu(Memory &memory,FrameBuffer &buffer, Input &input);

    void execute_instruction(const RegisterPair &oppcode);

    void update_timers();

    void cycle();

private:


    // amount of instructions per cycle
    u8 speed = 10;



    // store memory
    Memory &memory;

    FrameBuffer &buffer;
    
    Input &input;


    CpuState state = CpuState();
    OppInstructions opp;
};

#endif // CPU_H
