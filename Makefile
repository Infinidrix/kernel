
SOURCE := $(wildcard src/*/*.c)
HEADERS := $(wildcard src/*/*.h)

OBJ := $(patsubst src%c, build%o, $(SOURCE))

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

build/kernel/kernel.bin: build/kernel/kernel_entry.o $(OBJ)
	ld -o $@.temp -Ttext 0x1000 $^ --oformat binary -m elf_i386
	head -c 5120 $@.temp > $@
	rm $@.temp

$(OBJ) : build%o : src%c $(HEADERS)
	gcc -ffreestanding -c -m32 -fno-pie $< -o $@

boot: build/os-image
	qemu-system-x86_64 -drive format=raw,file=build/os-image,index=0,if=floppy

clean:
	rm build/boot/* build/drivers/* build/kernel/* build/os-image