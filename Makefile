
SOURCE := $(wildcard src/kernel/*.c src/drivers/*.c)
HEADERS := $(wildcard src/*/*.h)

USER_SOURCE := $(wildcard src/user/*.c src/stdlib/*.c)
USER_OBJ := $(patsubst src%c, build%o, $(USER_SOURCE))
OBJ := $(patsubst src%c, build%o, $(SOURCE))

build/os-image: build/boot/boot_trimmed.bin build/kernel/kernel.bin build/user/user
	cat $^ > $@

build/boot/boot_trimmed.bin: build/boot/boot.bin
	head -c 512 build/boot/boot.bin > build/boot/boot_trimmed.bin

build/boot/boot.bin: build/boot/boot.o
	ld -Ttext 0x7c00 --oformat binary -o build/boot/boot.bin build/boot/boot.o -m elf_i386

build/boot/boot.o: src/*/*.s src/boot/*/*.s
	as --32 src/boot/boot.s -o build/boot/boot.o

# USER BUILD
build/user/user: build/user/user_entry.o $(USER_OBJ)
	ld --Ttext 0x07048000 -m elf_i386 --oformat elf32-i386 -o $@ $^


build/user/user_entry.o: src/user/user_entry.s
	as --32 $^ -o $@

build/kernel/kernel_entry.o: src/kernel/kernel_entry.s
	as --32 $^ -o $@

build/kernel/kernel.bin: build/kernel/kernel_entry.o $(OBJ)
	ld -o $@.temp -Ttext 0x1000 $^ --oformat binary -m elf_i386
	head -c 5120 $@.temp > $@
	rm $@.temp

$(OBJ) : build%o : src%c $(HEADERS)
	gcc -ffreestanding -c -m32 -fno-pie $< -o $@
$(USER_OBJ) : build%o : src%c $(HEADERS)
	gcc -ffreestanding -c -m32 -fno-pie $< -o $@

boot: build/os-image
	qemu-system-x86_64 -drive format=raw,file=build/os-image,index=0,if=floppy

clean:
	rm build/boot/* build/drivers/* build/kernel/* build/os-image