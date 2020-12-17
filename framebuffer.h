#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "definitions.h"
class FrameBuffer
{
public:
    FrameBuffer();

    bool set_pixel(int x,int y);

    Color get_pixel(uint x,uint y);

    void reset();

private:
    uint width = WINDOW_WIDTH;
    uint height = WINDOW_HEIGHT;

     uint pixel_index(uint x, uint y);

    Color buffer[WINDOW_WIDTH*WINDOW_HEIGHT];

};

#endif // FRAMEBUFFER_H
