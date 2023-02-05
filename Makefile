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

objects = loader.o kernel.o gdt.o port.o screen.o

%.o : %.cpp
	$(CC) $(GPPPARAMS) -o $@ -c $<

%.o : %.s
	as $(ASPARAMS) -o $@ $<

kernel.bin : linker.ld $(objects)
	$(LK) $(LDPARAMS) -T $< -o $@ $(objects)

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "OS" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run : kernel.iso
	(killall vmware && sleep 1) || true
	vmware -x /home/jackwula/vmware/OS/OS.vmx
#	run your os in vmware virtualmachine.
#	.vmx needs to be created in advance manually.

clean :
	rm -rf iso
	rm $(objects) kernel.bin  kernel.iso