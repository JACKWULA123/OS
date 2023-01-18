void printf(char* str) {
    unsigned short* VideoMemory = (unsigned short*)0xb8000;

    for (int i = 0; str[i] != '\0'; i++) {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }

    return;
}

extern "C" int kernel(void* multiboot_struct, unsigned int magicNumber) {
    printf("hello,world!\n");

    while (1)
        ;

    return 0;
}