#include "cpu.h"
#include "sprites.h"
#include "bitwise.h"
cpu::cpu(Memory &memory,FrameBuffer &buffer, Input &input):memory(memory),buffer(buffer),input(input),opp(OppInstructions(memory,buffer,state,input))
{

    // adds sprites
    memory.write_to_interpreter(def::sprites);
    cycle();



}

void cpu::cycle () {
    for (uint c = 0; c < speed; c++) {
        if (!state.paused) {
            RegisterPair oppcode = RegisterPair(ByteRegister(memory.read(state.pc)), ByteRegister(memory.read(state.pc + 1)));
            execute_instruction(oppcode);
        }
    }

    if (!state.paused) {
        update_timers();
    }

    //this.playSound();
    //this.renderer.render();
}


void cpu::execute_instruction(const RegisterPair &pair) {
    state.pc = state.pc + 2;

    switch (pair.value() & 0xf000) {

        case 0x0000: {

            switch (pair.value()) {
                case 0x00E0:
                opp.oppcode_00E0();
                break;

                case 0x00EE:
                opp.oppcoe_00EE();
                break;

            }

            break;

        }
        case 0x1000:
            opp.oppcode_1nnn(pair);
         break;


        case 0x2000:
            opp.oppcode_2nnn(pair);
        break;

        case 0x3000:
            opp.oppcode_3xkk(pair);
            break;

        case 0x4000:
            opp.oppcode_4xkk(pair);
            break;

         case 0x5000:
            opp.oppcode_5xy0(pair);
            break;

        case 0x6000:
            opp.oppcode_6xkk(pair);
            break;

         case 0x7000:
            opp.oppcode_7xkk(pair);
         break;

        case 0x8000: {
                switch(bitwise::low_nibble(pair.low())) {

                case 0x0:
                    opp.oppcode_8xy0(pair);
                   break;
                 case 0x1:
                    opp.oppcode_8xy1(pair);
                    break;
                case 0x2:
                   opp.oppcode_8xy2(pair);
                   break;
                case 0x3:
                   opp.oppcode_8xy3(pair);
                   break;
                case 0x4:
                   opp.oppcode_8xy4(pair);
                   break;
                case 0x5:
                   opp.oppcode_8xy5(pair);
                   break;
                case 0x6:
                   opp.oppcode_8xy6(pair);
                   break;
                case 0x7:
                   opp.oppcode_8xy7(pair);
                   break;
                case 0xE:
                   opp.oppcode_8xyE(pair);
                   break;
              }



                break;
            }
        case 0x9000:
            opp.oppcode_9xy0(pair);
            break;

        case 0xA000:
            opp.oppcode_Annn(pair);
            break;

        case 0xB000:
            opp.oppcode_Bnnn(pair);
            break;

        case 0xC000:
            opp.oppcode_Cxkk(pair);
            break;

        case 0xD000:
            opp.oppcode_Dxyn(pair);
            break;

        case 0xE000: {
            switch(bitwise::low_nibble(pair.low())) {


            case 0xE:
                opp.oppcode_Ex9E(pair);
                break;
            case 0x1:
                opp.oppcode_ExA1(pair);
                break;


            }
            break;

        }
        case 0xF000: {

            switch(pair.low()) {

                case 0x7:
                opp.oppcode_Fx07(pair);
                break;

                case 0xA:
                    opp.oppcode_Fx0A(pair);

                break;

            case 0x15:
                opp.oppcode_Fx15(pair);
                break;

            case 0x18:
                opp.oppcode_Fx18(pair);
                break;

            case 0x1E:
                opp.oppcode_Fx1E(pair);
                break;

            case 0x29:
                opp.oppcode_Fx29(pair);
                break;

             case 0x33:
                opp.oppcode_Fx33(pair);
                break;

            case 0x55:
                opp.oppcode_Fx55(pair);
                break;

            case 0x65:
                opp.oppcode_Fx65(pair);
                break;
            default:
                break;


            }

           break;
        }

        default:
                break;


        }

    }


void cpu::update_timers() {

        if (state.delayTimer.value() > 0) {
            state.delayTimer.decrement();
        }

        if (state.soundTimer.value() > 0) {
            state.soundTimer.decrement();
        }

}
