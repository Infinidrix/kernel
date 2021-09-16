#include "loader.h"
#include "elf.h"
#include "../drivers/screen.h"

short is_elf(Elf32_Ehdr *header){
    char *identifier = header->e_ident;
    return (identifier[0] == (char)0x7f &&
            identifier[1] == 'E' &&
            identifier[2] == 'L' &&
            identifier[3] == 'F'
    );
}

void print_program(Elf32_Phdr *program, int offset){

    print(" Of: ");
    print_int_attr(offset, GREEN_ON_BLACK);
    print(" File Size: ");
    print_int_attr(program->p_filesz, GREEN_ON_BLACK);
    print(" Flags: ");
    print_int_attr(program->p_flags, GREEN_ON_BLACK);
    print(" Offset: ");
    print_int_attr(program->p_offset, GREEN_ON_BLACK);
    print(" Type: ");
    print_int_attr(program->p_type, GREEN_ON_BLACK);
    print(" V Addr: ");
    print_int_attr(program->p_vaddr, GREEN_ON_BLACK);
    print(" \n");
}

void print_section(Elf32_Shdr *section, int offset){
    print(" Of: ");
    print_int_attr(offset, GREEN_ON_BLACK);
    print(" Addr: ");
    print_int_attr(section->sh_addr, GREEN_ON_BLACK);
    print(" Entry Size: ");
    print_int_attr(section->sh_entsize, GREEN_ON_BLACK);
    print(" Section Offset: ");
    print_int_attr(section->sh_offset, GREEN_ON_BLACK);
    print(" Type: ");
    print_int_attr(section->sh_type, GREEN_ON_BLACK);
    print(" Section Size: ");
    print_int_attr(section->sh_size, GREEN_ON_BLACK);
    print(" \n");
}

// File name not useful here
void loader(char *filename){
    char * program = (char *) USER_PROG_START;
    Elf32_Ehdr * header = (Elf32_Ehdr *) program;
    if (!is_elf(header)){
        print("This is not a valid ELF");
        return;
    } 
    int offset = header->e_phoff;
    // print_int_attr((void *)header->e_phoff, WHITE_ON_BLACK);
    for (int i = 0; i < header->e_phnum; i++){
        Elf32_Phdr *program_header = (Elf32_Phdr *)(program + offset);
        print_program(program_header, offset);
        offset += header->e_phentsize;
    }
    // TODO: Fix print int
    offset = header->e_shoff;
    
    for (int i = 0; i < header->e_shnum; i++){
        // print("Section ");
        Elf32_Shdr *section_header = (Elf32_Shdr *) (program + offset);
        // print_int_attr((void *) section_header->sh_flags, WHITE_ON_BLACK);
        print_section(section_header, offset);
        offset += header->e_shentsize;
    }
    
}