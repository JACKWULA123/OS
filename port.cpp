// port.cpp

#include "port.h"
#include "type.h"

Port::Port(uint16_t _port_number) : port_number(_port_number) {}

Port::~Port() {}

/*-----------------------------------------------------------------------*/

Port8bit::Port8bit(uint16_t _port_number) : Port(_port_number) {}

Port8bit::~Port8bit() {}

uint8_t Port8bit::readData()
{
    uint8_t data;
    __asm__ volatile("inb %1, %0"
                     : "=a"(data)
                     : "Nd"(port_number));

    return data;
}

void Port8bit::writeData(uint8_t _data)
{
    __asm__ volatile("outb %0, %1"
                     :
                     : "a"(_data), "Nd"(port_number));

    return;
}

/*---------------------------------------------------------------------------*/

Port8bitSlow::Port8bitSlow(uint16_t _port_number) : Port8bit(_port_number) {}

Port8bitSlow::~Port8bitSlow() {}

void Port8bitSlow::writeData(uint8_t _data)
{
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:"
                     :
                     : "a"(_data), "Nd"(port_number));

    return;
}

/*---------------------------------------------------------------------------*/

Port16bit::Port16bit(uint16_t _port_number) : Port(_port_number) {}

Port16bit::~Port16bit() {}

uint16_t Port16bit::readData()
{
    uint16_t data;
    __asm__ volatile("inw %1, %0"
                     : "=a"(data)
                     : "Nd"(port_number));

    return data;
}

void Port16bit::writeData(uint16_t _data)
{
    __asm__ volatile("outw %0, %1"
                     :
                     : "a"(_data), "Nd"(port_number));
}

/*---------------------------------------------------------------------------*/

Port32bit::Port32bit(uint16_t _port_number) : Port(_port_number) {}

Port32bit::~Port32bit() {}

uint32_t Port32bit::readData()
{
    uint32_t data;
    __asm__ volatile("inl %1, %0"
                     : "=a"(data)
                     : "Nd"(port_number));

    return data;
}

void Port32bit::writeData(uint32_t _data)
{
    __asm__ volatile("outl %0, %1"
                     :
                     : "a"(_data), "Nd"(port_number));
}