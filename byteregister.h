#ifndef BYTEREGISTER_H
#define BYTEREGISTER_H

#include "definitions.h"

class ByteRegister
{
public:
    ByteRegister();
    explicit ByteRegister(const u8 value): val(value){}

    void set(const u8 val);

    void reset();

    u8 value () const;

    bool check_bit(const u8 bit) const;

    void set_bit_to (const u8 bit, const bool set);

    void increment();

    void decrement();

    ByteRegister& operator=(const u8 rhs);

    ByteRegister& operator=(const ByteRegister &rhs) {
        val = rhs.value();
        return *this;
    }

    ByteRegister& operator+=(const u8 rhs){
        this->val += rhs;
        return *this;
    }

    ByteRegister operator+(const u8 rhs) const {
        return ByteRegister(val + rhs);
    }

    bool operator!=(const u8 rhs) const {
        return val != rhs;
    }

    bool operator!=(const ByteRegister rhs) const {
        return val != rhs.value();
    }

    bool operator==(const u8 rhs) const;

    bool operator==(const ByteRegister &rhs) const;


private:
    u8 val = 0x0;

};

#endif // BYTEREGISTER_H
