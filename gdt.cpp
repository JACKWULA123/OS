// gdt.cpp

#include "gdt.h"

RamSegmentDescriptor::RamSegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags)
{
    uint8_t *target = (uint8_t *)this;
    // if limit is less than 1048576 which is 2^20, 1MB, the units of limit
    // will be byte, otherwise it will be page(4KB).
    if (limit < 1048576)
    {
        target[6] = 0x40;
        // set flags as the unit is byte.
    }
    else
    {
        // set the flags as the unit is page(4KB).
        target[6] = 0xc0;
        // if last four bytes of limit are less than 0xfff(2^12-1), page--;
        // unsolved?????????
        if ((limit & 0xfff) != 0xfff)
        {
            limit = (limit >> 12) - 1;
        }
        else
        {
            limit = limit >> 12;
        }
    }
    // set the rest of the RamDescriptor.
    target[0] = limit & 0xff;

    target[1] = (limit >> 8) & 0xff;

    target[6] = (limit >> 16) & 0xf | 0xc0;

    target[2] = base & 0xff;

    target[3] = (base >> 8) & 0xff;

    target[4] = (base >> 16) & 0xff;

    target[7] = (base >> 24) & 0xff;

    target[5] = flags;
}

uint32_t RamSegmentDescriptor::baseAddress()
{
    uint8_t *target = (uint8_t *)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t RamSegmentDescriptor::limitLen()
{
    uint8_t *target = (uint8_t *)this;
    uint32_t result = target[6] & 0xf;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];
    if ((target[6] & 0xc0) != 0xc0)
    {
        result = (result << 12) | 0xfff;
    }
    return result;
}

// RamSegmentDescriptor
/*----------------------------------------------------------------------------------------------------------------*/
// GlobalDescriptorTable

GlobalDescriptorTable::GlobalDescriptorTable()
    : null_RamSegmentDescriptor(0, 0, 0),
      unused_RamSegmentDescriptor(0, 0, 0),
      code_RamSegmentDescriptor(0, 64 * 1024 * 1024, 0x9a), // 0x9a(10011010)：kernelonly, excutable, readonly.
      data_RamSegmentDescriptor(0, 64 * 1024 * 1024, 0x92)  // 0x92(10010010)：kernelonly, unexcutable, read-write.
{
    uint32_t i[2];
    i[0] = (uint32_t)this;
    i[1] = sizeof(GlobalDescriptorTable) << 16;

    asm volatile("lgdt (%0)" ::"p"(((uint8_t *)i) + 2));
}

GlobalDescriptorTable::~GlobalDescriptorTable() {}

uint16_t GlobalDescriptorTable::codeSegmentSelector()
{
    return (uint8_t *)&code_RamSegmentDescriptor - (uint8_t *)this;
}

uint16_t GlobalDescriptorTable::dataSegmentselector()
{
    return (uint8_t *)&data_RamSegmentDescriptor - (uint8_t *)this;
}