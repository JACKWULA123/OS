// gdt.cpp

#include "gdt.h"

RamSegmentDescriptor::RamSegmentDescriptor(uint32_t _base, uint32_t _limit, uint8_t _flags)
{
    uint8_t *target = (uint8_t *)this;

    if (_limit < MIN_RAM_PAGING_LIMIT)
    {
        target[6] = RAM_PAGING_DISABLED;
    }
    else
    {
        target[6] = RAM_PAGING_ENABLED;

        if (doNeedLastPage(_limit))
        {
            _limit = (_limit >> 12) - 1;
        }
        else
        {
            _limit = _limit >> 12;
        }
    }
    // set the rest of the RamDescriptor.
    target[0] = _limit & 0xff;

    target[1] = (_limit >> 8) & 0xff;

    target[6] |= (_limit >> 16) & 0xf;

    target[2] = _base & 0xff;

    target[3] = (_base >> 8) & 0xff;

    target[4] = (_base >> 16) & 0xff;

    target[7] = (_base >> 24) & 0xff;

    target[5] = _flags;
}

bool RamSegmentDescriptor::doNeedLastPage(uint32_t _limit)
{
    if ((_limit & 0xfff) != 0xfff)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool RamSegmentDescriptor::doNeedLastPage(uint8_t _limit)
{
    if ((_limit & RAM_PAGING_ENABLED) != RAM_PAGING_ENABLED)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    if (doNeedLastPage(target[6]))
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
      code_RamSegmentDescriptor(0, 64 MB__, KERNELONLY_EXCUTABLE_READONLY),
      data_RamSegmentDescriptor(0, 64 MB__, KERNELONLY_UNEXCUTABLE_READWRITE)
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