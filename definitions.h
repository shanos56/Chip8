#pragma once

#include <cstdint>
#include <cstdlib>

using uint = unsigned int;

using u8 = uint8_t;
using u16 = uint16_t;
using s8 = int8_t;
using s16 = int16_t;

const uint WINDOW_HEIGHT = 32;
const uint WINDOW_WIDTH = 64;

const uint PROGRAM_BEGINNING = 0x200; // address where rom/game begins
const uint INTERPRETER_BEGINNING = 0x00; // address memory not used by rom


struct Noncopyable {
    Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable() = default;
    ~Noncopyable() = default;
};


enum class Color {
    white,
    black
};

class Cycles {
public:
    Cycles(uint nCycles) : cycles(nCycles) {}

    const uint cycles;
};
