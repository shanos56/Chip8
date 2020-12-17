#ifndef ADDRESS_H
#define ADDRESS_H

#include "definitions.h"
#include "byteregister.h"
#include "wordregister.h"
#include "registerpair.h"
class Address
{
public:
    Address(u16 location);
    explicit Address(const RegisterPair& from);
    explicit Address(const WordRegister& from);

    u16 value() const;

    bool in_range(Address low, Address high) const;

    bool operator==(u16 other) const;
    Address operator+(uint other) const;
    Address operator-(uint other) const;

private:
    u16 addr = 0x0;

};

#endif // ADDRESS_H
