#Makefile 

CC = g++
LK = ld

GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-leading-underscore -fno-exceptions -fno-rtti -fno-pie
#	-m32 : compile in 32 bit mode.
#	-fno-use-cxa-atexit : disable the C destructor __cxa_atexit.
#	-nostdlib : not to link with glibc.
#	-fno-builtin : disable the C built-in function.
#	-fno-leading-underscore : no underscore before the C identifier.
#	-fno-exceptions : disable the C++ exception class.
#	-fno-rtti : disable runtime info.
#	-fno-pie : disable pie mode.
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o : %.cpp
	$(CC) $(GPPPARAMS) -o $@ -c $<

%.o : %.s
	as $(ASPARAMS) -o $@ $<

kernel.bin : linker.ld $(objects)
	$(LK) $(LDPARAMS) -T $< -o $@ $(objects)

install : kernel.bin
	sudo cp $< /boot/kernel.bin