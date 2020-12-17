#ifndef INPUT_H
#define INPUT_H


#include "definitions.h"
#include <vector>

#include <functional>


enum CButton : uint {
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    A,
    B,
    C,
    D,
    E,
    F
};

class Input
{
public:
    Input();

    void button_pressed (CButton button);
    void button_released (CButton button);

    bool is_pressed(CButton button) const;

    void onNextKeyPress(std::function<void (CButton)> m_callback);
    
    void next_press (CButton button);

    void set_button(CButton button, bool set);

    bool is_pressed(u8 BCode) const;

    
    

  private:
    bool pressed[16] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

    bool button_switch = false;
    bool direction_switch = false;

    bool on_next = false;

    std::function<void (CButton)> m_callback;

};



#endif // INPUT_H
