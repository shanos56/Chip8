#include "byteregister.h"
#include "bitwise.h"
ByteRegister::ByteRegister()
{

}

void ByteRegister::set(const u8 value) {
    val = value;
}

void ByteRegister::reset() {
    val = 0;
}

u8 ByteRegister::value () const {
    return val;
}

bool ByteRegister::check_bit(const u8 bit) const {
    return bitwise::check_bit(val,bit);
}

void ByteRegister::set_bit_to (const u8 bit, const bool set) {
    val = bitwise::set_bit_to(val,bit,set);
}

void ByteRegister::increment() {
    val++;
}

void ByteRegister::decrement() {
    val--;
}

bool ByteRegister::operator==(const u8 rhs) const {
    return val == rhs;
}


bool ByteRegister::operator==(const ByteRegister &rhs) const {
    return val == rhs.value();
}


ByteRegister& ByteRegister::operator=(const u8 rhs) {
    set(rhs);
    return *this;
}
