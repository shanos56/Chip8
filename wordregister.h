#ifndef WORDREGISTER_H
#define WORDREGISTER_H

#include "definitions.h"

class WordRegister
{
public:
    WordRegister();

    void set (u16 value);

    u16 value() const;

    u8 low() const;
    u8 high ()  const;

    void increment ();
    void decrement ();

private:
    u16 val;
};

#endif // WORDREGISTER_H
