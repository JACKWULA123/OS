// screen.h

#ifndef SCREEN_H
#define SCREEN_H

#include "type.h"

#define VRAM_STARTING_POSITION 0xb8000
#define BASE_SCREEN_WIDTH 80
#define BASE_SCREEN_HEIGHT 25

class VGA_Screen
{
private:
    int16_t width;
    int16_t height;

    uint16_t *cursor;

public:
    void printf(char *_str);

    void clearScreen();
    void clearScreen(uint32_t _pix);

    void lineFeed();

    VGA_Screen(int16_t _width = BASE_SCREEN_WIDTH, int16_t _height = BASE_SCREEN_HEIGHT, uint16_t *_cursor = (uint16_t *)VRAM_STARTING_POSITION);

    ~VGA_Screen();
};

#endif