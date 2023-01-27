// gdt.cpp

#include "type.h"

class RamSegmentDescriptor
{
private:
    uint16_t limit_0_15;
    uint16_t base_16_31;
    uint8_t base_32_39;
    uint8_t access_40_47;
    uint8_t limit_48_51_flags_52_55;
    uint8_t base_56_63;

public:
    RamSegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);

    // combine and return the base address.
    uint32_t baseAddress();

    // combine and return the limit.
    uint32_t limitLen();
} __attribute__((packed));

class GlobalDescriptorTable
{
public:
    RamSegmentDescriptor null_RamSegmentDescriptor;
    RamSegmentDescriptor unused_RamSegmentDescriptor;
    RamSegmentDescriptor code_RamSegmentDescriptor;
    RamSegmentDescriptor data_RamSegmentDescriptor;

    GlobalDescriptorTable();

    ~GlobalDescriptorTable();

    uint16_t codeSegmentSelector();

    uint16_t dataSegmentselector();
};