// screen.cpp

#include "screen.h"

VGA_Screen::VGA_Screen(int16_t _width, int16_t _height, uint16_t *_cursor)
    : width(_width),
      height(_height),
      cursor(_cursor)
{
}

VGA_Screen::~VGA_Screen() {}

void VGA_Screen::printf(char *_str)
{

    for (; *_str != '\0'; _str++)
    {
        switch (*_str)
        {
        case '\n':
            lineFeed();
            break;

        default:
            *cursor = (*cursor & 0xFF00) | *_str;
            cursor++;
            break;
        }
    }

    return;
}

void VGA_Screen::clearScreen()
{

    while (cursor > (uint16_t *)VRAM_STARTING_POSITION)
    {
        cursor--;
        *cursor &= 0xff00;
    }

    return;
}

void VGA_Screen::clearScreen(uint32_t _pix)
{

    while (_pix)
    {
        cursor--;
        *cursor &= 0xff00;
        _pix--;
    }

    return;
}

void VGA_Screen::lineFeed()
{
    cursor += width - ((cursor - (uint16_t *)VRAM_STARTING_POSITION + 1) % width);
    cursor++;
}