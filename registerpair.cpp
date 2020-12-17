#include "registerpair.h"



void RegisterPair::set (u16 value) {
    low_byte.set(static_cast<u8>(value));
    high_byte.set(static_cast<u8>(value >> 8));
}

u16 RegisterPair::value() const {
    return static_cast<u16>((high_byte.value() << 8) | low_byte.value());
}

u8 RegisterPair::low() const {
    return low_byte.value();
}
u8 RegisterPair::high ()  const {
    return high_byte.value();
}

void RegisterPair::increment () {
    set(value()+1);
}
void RegisterPair::decrement () {
     set(value()-1);
}
