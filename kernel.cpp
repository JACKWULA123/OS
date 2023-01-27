// kernel.cpp
#include "type.h"
#include "gdt.h"

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

void printOnScreen(char *str)
{
    static uint16_t *video_memory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }

    return;
}

extern "C" int kernelMain(void *multiboot_struct, uint32_t magic_umber)
{
    GlobalDescriptorTable gdt;

    printOnScreen("gdt created successfully.");

    return 0;
}