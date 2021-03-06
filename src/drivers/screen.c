#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0X3d4
#define REG_SCREEN_DATA 0x3d5

#include "screen.h"
#include "../kernel/low_level.h"
#include "../kernel/utils.h"


void print_char(char character, int col, int row, char attribute_byte){
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }
    int offset;

    if (col >= 0 && row >= 0){
        offset = get_screen_offset(col, row);
    } else {
        offset = get_cursor();
    }

    if (character == '\n'){
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
    } else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }

    offset += 2;
    offset = handle_scrolling(offset);

    set_cursor(offset);
}

int get_screen_offset(int col, int row){
    return (row * MAX_COLS + col) * 2;
}

void set_cursor(int offset){
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

int get_cursor(){
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void print_at(char* message, int col, int row) {
    print_at_attr(message, col, row, WHITE_ON_BLACK);
}

void print(char *message) {
    print_at(message, -1, -1);
}

void print_attr(char *message, char attr){
    print_at_attr(message, -1, -1, attr);
}

void print_int_attr(int number, char attr){
    char result[10];
    print_at_attr(int_to_string(result, (unsigned int) number), -1, -1, attr);
}

void print_short_attr(short number, char attr){
    char result[10];
    print_at_attr(short_to_string(result, ((unsigned short) (number && 0xffff))), -1, -1, attr);
}

void print_at_attr(char* message, int col, int row, char attr) {
    if (col >= 0 && row >= 0){
        set_cursor(get_screen_offset(col, row));
    }
    int i = 0;
    while (message[i] != 0){
        print_char(message[i++], col, row, attr);
    }
}

void clear_screen() {
    int row = 0;
    int col = 0;

    for (row = 0; row < MAX_ROWS; row++){
        for (col = 0; col < MAX_COLS; col++){
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }
    set_cursor(get_screen_offset(0, 0));
}

int handle_scrolling(int cursor_offset){
    if (cursor_offset < MAX_ROWS * MAX_COLS * 2) {
        return cursor_offset;
    }
    int i;
    for (i = 1; i < MAX_ROWS; i++) {
        memory_copy((char *) (get_screen_offset(0, i) + VIDEO_ADDRESS),
            (char *) (get_screen_offset(0, i - 1) + VIDEO_ADDRESS),
            MAX_COLS * 2
        );
    }

    char* last_line = (char *) get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    for (i=0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    cursor_offset -= 2*MAX_COLS;

    return cursor_offset;
}