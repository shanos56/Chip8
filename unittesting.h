#ifndef UNITTESTING_H
#define UNITTESTING_H

#include "cpu.h"
#include "definitions.h"
#include "byteregister.h"
#include "address.h"
#include "registerpair.h"
#include "input.h"
#include "wordregister.h"
#include "framebuffer.h"
#include "oppinstructions.h"
#include "sprites.h"
#include <iostream>

#include <string>
class UnitTesting {
    
    
    
    UnitTesting() {
        
    }
    
    void test (bool test,std::string success, std::string err) {
        
        if (test) {
            std::cout << success << std::endl;
        } else {
            std::cout << err << std::endl;
        }
    }
    
    void test_memory() {
        Memory mem;
        Address addr = Address(0);
        
        mem.write(addr,def::sprites);
        
        test(mem.read(addr) == 0xf0,"Successfully inserted sprites to address","failed to add sprites to address");
        test()
        
        
    }
    
    
    void test_oppinstructions ();
    
    
    
};



#endif // UNITTESTING_H
