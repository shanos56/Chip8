#ifndef REGISTERPAIR_H
#define REGISTERPAIR_H

#include "definitions.h"
#include "byteregister.h"

class RegisterPair
{
public:
    RegisterPair(ByteRegister high, ByteRegister low): low_byte(low),high_byte(high) {}

    void set (u16 value);

    u16 value() const;

    u8 low() const;
    u8 high ()  const;

    void increment ();
    void decrement ();



private:

    ByteRegister low_byte;
    ByteRegister high_byte;

};

#endif // REGISTERPAIR_H
