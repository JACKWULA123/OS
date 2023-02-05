// kernel.cpp
#include "type.h"
#include "gdt.h"
#include "screen.h"

typedef void (*constructor)();

extern "C" constructor start_ctors;

extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i += 1)
    {
        (*i)();
    }
}

extern "C" int kernelMain(void *multiboot_struct, uint32_t magic_umber)
{
    GlobalDescriptorTable gdt;

    VGA_Screen screen;

    screen.printf("---------|\n---------|");

    screen.clearScreen(1);

    screen.printf("nice!");

    return 0;
}