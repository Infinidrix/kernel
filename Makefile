build/os-image: build/boot/boot_trimmed.bin build/kernel/kernel.bin
	cat build/boot/boot.bin build/kernel/kernel.bin > build/os-image

build/boot/boot_trimmed.bin: build/boot/boot.bin
	head -c 512 build/boot/boot.bin > build/boot/boot_trimmed.bin

build/boot/boot.bin: build/boot/boot.o
	ld -Ttext 0x7c00 --oformat binary -o build/boot/boot.bin build/boot/boot.o -m elf_i386

build/boot/boot.o: src/*/*.s src/boot/*/*.s
	as --32 src/boot/boot.s -o build/boot/boot.o

build/kernel/kernel_entry.o: src/kernel/kernel_entry.s
	as --32 $^ -o $@

build/kernel/kernel.bin: build/kernel/kernel_entry.o build/kernel/kernel.o build/kernel/low_level.o build/drivers/screen.o
	ld -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

build/kernel/kernel.o: src/kernel/kernel.c
	gcc -ffreestanding -c -m32 -fno-pie $^ -o $@

build/kernel/low_level.o: src/kernel/low_level.c
	gcc -ffreestanding -c -m32 -fno-pie $^ -o $@

build/drivers/screen.o: src/drivers/screen.c
	gcc -ffreestanding -c -m32 -fno-pie $^ -o $@
boot: build/os-image
	qemu-system-x86_64 -drive format=raw,file=build/os-image,index=0,if=floppy
