#include "loader.h"
#include "elf.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "program_control_block.h"

short is_elf(Elf32_Ehdr *header){
    char *identifier = header->e_ident;
    return (identifier[0] == (char)0x7f &&
            identifier[1] == 'E' &&
            identifier[2] == 'L' &&
            identifier[3] == 'F'
    );
}
// Print program headers for debugging purposes
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
// Print section headers for debugging purposes
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


void print_symbol_entry(Elf32_Sym *entry){
    print("Name Idx: ");
    print_int_attr(entry->st_name, GREEN_ON_BLACK);
    print(" Value: ");
    print_int_attr(entry->st_value, GREEN_ON_BLACK);
    print(" Size: ");
    print_int_attr(entry->st_size, GREEN_ON_BLACK);
}

int get_main_index(Elf32_Shdr *strtab, char * program){
    int size, offset, start, index;
    index = 0;
    size = strtab->sh_size - 1;
    offset = ((int) program) + strtab->sh_offset + 1;
    start = offset;
    while (offset < start + size ){
        if (strcmp((char *)(offset), "main")){
            return offset - start + 1;
        }
        index++;
        offset += strlen((char *)(offset)) + 1;
    }
    print("Why like this?");
    return 0;
} 

int find_index(Elf32_Shdr *symtab, int main_index, char * program){
    int size = symtab->sh_size;
    int ent_size = symtab->sh_entsize;
    int offset = (int) (program + symtab->sh_offset);
    for (int i = 0; i < size; i += ent_size){
        Elf32_Sym *symbol_ent = (Elf32_Sym *)(offset + i);
        if (symbol_ent->st_name == main_index){
            return symbol_ent->st_value;
        }
    }
    print("Why This?");
    return 0;

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
    int start;
    for (int i = 0; i < header->e_phnum; i++){
        Elf32_Phdr *program_header = (Elf32_Phdr *)(program + offset);
        if (program_header->p_type == PT_LOAD){
            memset((char *)(program_header->p_vaddr), (char) 0, program_header->p_memsz);
            memory_copy((char *)(program + program_header->p_offset), (char *)(program_header->p_vaddr), program_header->p_filesz);
        }
        offset += header->e_phentsize;
    }

    Elf32_Shdr *symbol_table, *string_table;
    string_table = (void *)'\0';
    offset = header->e_shoff;
    for (int i = 0; i < header->e_shnum; i++){
        Elf32_Shdr *section_header = (Elf32_Shdr *) (program + offset);
        if (section_header->sh_type == SHT_SYMTAB){
            symbol_table = section_header;
        } else if (section_header->sh_type == SHT_STRTAB && string_table == (void *)'\0'){
            string_table = section_header;
        }
        offset += header->e_shentsize; 
    }
    int main_index = get_main_index(string_table, program);
    start = find_index(symbol_table, main_index, program);
    print_attr("Starting User Program\n", GREEN_ON_BLACK);
    // TODO: Choose one of the two as way to jump to start
    thread_action action = (thread_action) start;
    // action((void *) 0);
    pthread_init((thread_action) start);
    // ((int *(*)()) start)();
    /*
    __asm__("call %%eax"
        :
        : "a" (start)
    );
    */
    print_attr("\nFinished User Program", YELLOW_ON_BLUE);
    
}
