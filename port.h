// port.h
#ifndef PORT_H
#define PORT_H

#include "type.h"

class Port
{
protected:
    uint16_t port_number;

    // make constructor protected so the class will not be instantiated.
    // constructor can not be virtual.
    Port(uint16_t _port_number);

    ~Port();
};

class Port8bit : public Port
{
public:
    virtual void writeData(uint8_t _data);

    virtual uint8_t readData();

    Port8bit(uint16_t _port_number);

    ~Port8bit();
};

class Port8bitSlow : public Port8bit
{
public:
    virtual void writeData(uint8_t _data);

    Port8bitSlow(uint16_t _port_number);

    ~Port8bitSlow();
};

class Port16bit : public Port
{
public:
    virtual void writeData(uint16_t _data);

    virtual uint16_t readData();

    Port16bit(uint16_t _port_number);

    ~Port16bit();
};

class Port32bit : public Port
{
public:
    virtual void writeData(uint32_t _data);

    virtual uint32_t readData();

    Port32bit(uint16_t _port_number);

    ~Port32bit();
};

#endif