build/os-image: build/boot/boot.bin build/kernel/kernel.bin
	cat build/boot/boot.bin build/kernel/kernel.bin > build/os-image

build/boot/boot.bin: build/boot/boot.o
	ld -Ttext 0x7c00 --oformat binary -o build/boot/boot.bin build/boot/boot.o

build/boot/boot.o: src/*/*.s src/boot/*/*.s
	as src/boot/boot.s -o build/boot/boot.o

build/kernel/kernel.bin: build/kernel/kernel.o
	ld -o build/kernel/kernel.bin -Ttext 0x1000 build/kernel/kernel.o --oformat binary

build/kernel/kernel.o: src/kernel/*.c
	gcc -ffreestanding -c src/kernel/kernel.c -o build/kernel/kernel.o
boot: build/os-image
	qemu-system-x86_64 -drive format=raw,file=build/os-image,index=0,if=floppy
