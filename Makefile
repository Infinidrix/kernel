build/boot/boot.bin: build/boot/boot.o
	ld -Ttext 0x7c00 --oformat binary -o build/boot/boot.bin build/boot/boot.o

build/boot/boot.o: src/boot/boot.s src/boot/utils-16/*.s src/boot/utils-32/*.s
	as src/boot/boot.s -o build/boot/boot.o

boot: build/boot/boot.bin
	qemu-system-x86_64 -drive format=raw,file=build/boot/boot.bin,index=0,if=floppy
