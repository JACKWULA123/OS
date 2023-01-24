#ifndef TYPE_H_
#define TYPE_H_
#include "type.h"
#endif

typedef void (*Constructor)();

extern "C" Constructor start_ctors;

extern "C" Constructor end_ctors;

extern "C" void callConstructors() {
    for (Constructor* i = &start_ctors; i != &end_ctors; i += 1) {
        (*i)();
    }
}

void printOnScreen(char* str) {
    static uint16_t* video_memory = (uint16_t*)0xb8000;

    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }

    return;
}

extern "C" int kernelMain(void* multiboot_struct, uint32_t magicNumber) {
    printOnScreen("hello,world!");

    return 0;
}