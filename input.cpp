#include "input.h"

Input::Input()
{

}


void Input::next_press (CButton button) {
    m_callback(button);
    this->on_next = false;
}

void Input::button_pressed (CButton button) {
    pressed[button] = true;

    // Make sure onNextKeyPress is initialized and the pressed key is actually mapped to a Chip-8 key
    if (on_next) {
        next_press(button);
    }
}



void Input::onNextKeyPress(std::function<void (CButton)> m_callback) {
    this->on_next = true;
    this->m_callback = m_callback;

}
void Input::button_released (CButton button) {
    this->pressed[button] = false;
}

bool Input::is_pressed (CButton button) const {
    return this->pressed[button];
}
bool Input::is_pressed (u8 BCode) const {
    return this->pressed[BCode];
}
void Input::set_button(CButton button, bool set) {
    this->pressed[button] = set;
}

