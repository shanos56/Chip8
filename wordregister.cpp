#include "wordregister.h"

WordRegister::WordRegister()
{

}



void WordRegister::set (u16 value) {
   val = value;
}

u16 WordRegister::value() const {
   return val;
}

u8 WordRegister::low() const {
    return static_cast<u8>(val);
}
u8 WordRegister::high ()  const {
    return static_cast<u8>(val >> 8);
}

void WordRegister::increment () {
    val++;
}
void WordRegister::decrement () {
     val--;
}
