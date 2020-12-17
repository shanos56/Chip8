#include "framebuffer.h"

FrameBuffer::FrameBuffer()
{

}
bool FrameBuffer::set_pixel(int x,int y) {

    if (x > width) {
        x -= width;
    } else if (x < 0) {
        x += width;
    }

    if (y > height) {
        y -= height;
    } else if (y < 0) {
        y += height;
    }
    Color col;

    // pixel is xor ed onto screen
    // if pixel is already black it becomes white
    if (get_pixel(x,y)  == Color::black) {
        buffer[pixel_index(x,y)] = Color::white;
        return false;
    } else {
         buffer[pixel_index(x,y)] = Color::black;
         return true;
    }
}

Color FrameBuffer::get_pixel(uint x,uint y) {
    return buffer[pixel_index(x,y)];
}

uint FrameBuffer::pixel_index(uint x, uint y) {
    return (y * width) + x;

}

void FrameBuffer::reset() {
    for (uint var = 0; var < sizeof(buffer) / sizeof(buffer[0]); ++var) {
        buffer[var] = Color::white;
    }
}
