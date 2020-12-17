#ifndef BITWISE_H
#define BITWISE_H

#include "definitions.h"
namespace bitwise {

    /**
     * @brief compose_bits
     * @param high
     * @param low
     * @return
     */
    inline u8 compose_bits(const u8 high, const u8 low) {
        return static_cast<u8>(high << 1 | low);
    }

    /**
     * @brief compose_nibbles
     *      grabs the bottom 4 bits of high and integrates with the top 4 bits of low
     * @param high
     * @param low
     * @return
     */
    inline u8 compose_nibbles(const u8 high, const u8 low) {
        return static_cast<u8>((high << 4) | low);
    }


    /*
     * @description turns bit from 0 to 1
     * @param val value to change
     * @param bit bit number to change (0-7)
     *
     * */
    inline u8 set_bit (const u8 val, const u8 bit) {
        return static_cast<u8> (val | (1 << bit));
    }
    /**
     * @brief low_nibble grabs last four bits of eight bit binary
     * @param val eight bits to get value
     * @return
     */
    inline u8 low_nibble(const u8 val) {
        return static_cast<u8>(0xF & val);
    }
    /**
     * @brief high_nibble grabs first four bits of eight bit binary
     * @param val  eight bits to get value
     * @return
     */
    inline u8 high_nibble(const u8 val) {
        return static_cast<u8>((0xF0 & val) >> 4);
    }
    /*
     * @description turns bit from 1 to 0
     * @param val value to change
     * @param bit bit number to change (0-7)
     *
     * */
    inline u8 clear_bit(const u8 val, const u8 bit) {
        return static_cast<u8>(val & ~(1 << bit));
    }

    /*
     * @description turns bit, in val, to 1 if set is true otherwise changes it to false
     * @param val value to change
     * @param bit bit number to change (0-7)
     *
     * */
    inline u8 set_bit_to (const u8 val, const u8 bit, const bool set) {

          return set ? set_bit(val,bit) : clear_bit(val,bit);

    }

    /*
     * @description appends bits together to make 16 bit integer
     * @param high top 8 bits in binary
     * @param low bottom 8 bits of binary
     *
     * */
    inline u16 compose_bytes (const u8 high, const u8 low) {
       return static_cast<u16>((high << 8) | low);
    }


    /*
     * @description determines if bit is turned on
     * @param val value check
     * @param bit bit number to check (0-7)
     *
     * */
    inline bool check_bit (const u8 val, const u8 bit) {
       return (val & (1 << bit)) != 0;
    }

}

#endif // BITWISE_H
