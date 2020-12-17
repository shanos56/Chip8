#include "memory.h"

Memory::Memory()
{
memory = std::vector<u8>(4096);
}

void Memory::write_to_interpreter(const std::vector<u8> &arr) {
    write(Address(INTERPRETER_BEGINNING),arr);
}

void Memory::write(const Address &addr, const std::vector<u8> &arr) {
    for (uint i = 0; i < arr.size();i++) {
        memory.at(addr.value() + i ) = arr.at(i);
    }
}

void Memory::write(const WordRegister &addr, const u8 &byte) {
    memory.at(addr.value()) = byte;
}

void Memory::write(const Address &addr, const u8 &byte) {
    memory.at(addr.value()) = byte;
}

u8 Memory::read(const Address &addr) const {
    return memory.at(addr.value());
}


void Memory::clear() {
    memory.clear();
    
}
