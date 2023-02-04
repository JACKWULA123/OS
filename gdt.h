// gdt.cpp

#include "type.h"

#define RAM_PAGING_DISABLED 0x40
#define RAM_PAGING_ENABLED 0xc0
#define MIN_RAM_PAGING_LIMIT 1048576 // 2^20
#define KERNELONLY_EXCUTABLE_READONLY 0x9a
#define KERNELONLY_UNEXCUTABLE_READWRITE 0x92

#define KB__ *1024
#define MB__ *1048576
#define GB__ *1073741824

class RamSegmentDescriptor
{
private:
    uint16_t limit_0_15;
    uint16_t base_16_31;
    uint8_t base_32_39;
    uint8_t access_40_47;
    uint8_t limit_48_51_flags_52_55;
    uint8_t base_56_63;

    bool doNeedLastPage(uint32_t _limit);
    bool doNeedLastPage(uint8_t _limit);

public:
    RamSegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);

    // combine and return the base address.
    uint32_t baseAddress();

    // combine and return the limit.
    uint32_t limitLen();
} __attribute__((packed));
// memory alignment disabled.

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