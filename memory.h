#ifndef MEMORY_H
#define MEMORY_H

#include "definitions.h"
#include "address.h"
#include <vector>

class Memory
{
public:
    Memory();

    void write_to_interpreter(const std::vector<u8> &arr);

    void write(const Address &addr, const std::vector<u8> &arr);

    void write(const Address &addr, const u8 &byte);
    
    void write(const WordRegister &addr, const u8 &byte);

    
    void clear();

    u8 read(const Address &addr) const;

    private:
        std::vector<u8> memory;
};

#endif // MEMORY_H
